#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubi_wl_entry {int pnum; } ;
struct TYPE_2__ {int /*<<< orphan*/  rb_node; } ;
struct ubi_device {scalar_t__ works_count; scalar_t__ vid_hdr_aloffset; scalar_t__ peb_size; int /*<<< orphan*/  wl_lock; int /*<<< orphan*/  fm_eba_sem; int /*<<< orphan*/  works; TYPE_1__ free; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int produce_free_peb (struct ubi_device*) ; 
 int /*<<< orphan*/  prot_queue_add (struct ubi_device*,struct ubi_wl_entry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,...) ; 
 int ubi_self_check_all_ff (struct ubi_device*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 struct ubi_wl_entry* wl_get_wle (struct ubi_device*) ; 

int ubi_wl_get_peb(struct ubi_device *ubi)
{
	int err;
	struct ubi_wl_entry *e;

retry:
	down_read(&ubi->fm_eba_sem);
	spin_lock(&ubi->wl_lock);
	if (!ubi->free.rb_node) {
		if (ubi->works_count == 0) {
			ubi_err(ubi, "no free eraseblocks");
			ubi_assert(list_empty(&ubi->works));
			spin_unlock(&ubi->wl_lock);
			return -ENOSPC;
		}

		err = produce_free_peb(ubi);
		if (err < 0) {
			spin_unlock(&ubi->wl_lock);
			return err;
		}
		spin_unlock(&ubi->wl_lock);
		up_read(&ubi->fm_eba_sem);
		goto retry;

	}
	e = wl_get_wle(ubi);
	prot_queue_add(ubi, e);
	spin_unlock(&ubi->wl_lock);

	err = ubi_self_check_all_ff(ubi, e->pnum, ubi->vid_hdr_aloffset,
				    ubi->peb_size - ubi->vid_hdr_aloffset);
	if (err) {
		ubi_err(ubi, "new PEB %d does not contain all 0xFF bytes", e->pnum);
		return err;
	}

	return e->pnum;
}