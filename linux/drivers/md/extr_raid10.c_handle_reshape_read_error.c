#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct r10conf {int copies; TYPE_1__* mirrors; int /*<<< orphan*/  prev; } ;
struct r10bio {int sectors; TYPE_2__* devs; int /*<<< orphan*/  sector; } ;
struct page {int dummy; } ;
struct mddev {int /*<<< orphan*/  recovery; struct r10conf* private; } ;
struct md_rdev {int /*<<< orphan*/  nr_pending; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_6__ {struct page** pages; } ;
struct TYPE_5__ {int devnum; scalar_t__ addr; int /*<<< orphan*/  bio; } ;
struct TYPE_4__ {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  MD_RECOVERY_INTR ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  __raid10_find_phys (int /*<<< orphan*/ *,struct r10bio*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devs ; 
 TYPE_3__* get_resync_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct r10bio*) ; 
 struct r10bio* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct md_rdev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rdev_dec_pending (struct md_rdev*,struct mddev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct r10bio*,int /*<<< orphan*/ ,int) ; 
 int sync_page_io (struct md_rdev*,scalar_t__,int,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_reshape_read_error(struct mddev *mddev,
				     struct r10bio *r10_bio)
{
	/* Use sync reads to get the blocks from somewhere else */
	int sectors = r10_bio->sectors;
	struct r10conf *conf = mddev->private;
	struct r10bio *r10b;
	int slot = 0;
	int idx = 0;
	struct page **pages;

	r10b = kmalloc(struct_size(r10b, devs, conf->copies), GFP_NOIO);
	if (!r10b) {
		set_bit(MD_RECOVERY_INTR, &mddev->recovery);
		return -ENOMEM;
	}

	/* reshape IOs share pages from .devs[0].bio */
	pages = get_resync_pages(r10_bio->devs[0].bio)->pages;

	r10b->sector = r10_bio->sector;
	__raid10_find_phys(&conf->prev, r10b);

	while (sectors) {
		int s = sectors;
		int success = 0;
		int first_slot = slot;

		if (s > (PAGE_SIZE >> 9))
			s = PAGE_SIZE >> 9;

		rcu_read_lock();
		while (!success) {
			int d = r10b->devs[slot].devnum;
			struct md_rdev *rdev = rcu_dereference(conf->mirrors[d].rdev);
			sector_t addr;
			if (rdev == NULL ||
			    test_bit(Faulty, &rdev->flags) ||
			    !test_bit(In_sync, &rdev->flags))
				goto failed;

			addr = r10b->devs[slot].addr + idx * PAGE_SIZE;
			atomic_inc(&rdev->nr_pending);
			rcu_read_unlock();
			success = sync_page_io(rdev,
					       addr,
					       s << 9,
					       pages[idx],
					       REQ_OP_READ, 0, false);
			rdev_dec_pending(rdev, mddev);
			rcu_read_lock();
			if (success)
				break;
		failed:
			slot++;
			if (slot >= conf->copies)
				slot = 0;
			if (slot == first_slot)
				break;
		}
		rcu_read_unlock();
		if (!success) {
			/* couldn't read this block, must give up */
			set_bit(MD_RECOVERY_INTR,
				&mddev->recovery);
			kfree(r10b);
			return -EIO;
		}
		sectors -= s;
		idx++;
	}
	kfree(r10b);
	return 0;
}