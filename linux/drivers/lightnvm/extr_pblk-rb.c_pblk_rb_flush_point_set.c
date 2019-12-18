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
struct TYPE_2__ {int /*<<< orphan*/  bios; } ;
struct pblk_rb_entry {TYPE_1__ w_ctx; } ;
struct pblk_rb {unsigned int nr_entries; int /*<<< orphan*/  flush_point; struct pblk_rb_entry* entries; int /*<<< orphan*/  inflight_flush_point; int /*<<< orphan*/  sync; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  pblk_rb_sync_end (struct pblk_rb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_rb_sync_init (struct pblk_rb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int pblk_rb_flush_point_set(struct pblk_rb *rb, struct bio *bio,
				   unsigned int pos)
{
	struct pblk_rb_entry *entry;
	unsigned int sync, flush_point;

	pblk_rb_sync_init(rb, NULL);
	sync = READ_ONCE(rb->sync);

	if (pos == sync) {
		pblk_rb_sync_end(rb, NULL);
		return 0;
	}

#ifdef CONFIG_NVM_PBLK_DEBUG
	atomic_inc(&rb->inflight_flush_point);
#endif

	flush_point = (pos == 0) ? (rb->nr_entries - 1) : (pos - 1);
	entry = &rb->entries[flush_point];

	/* Protect flush points */
	smp_store_release(&rb->flush_point, flush_point);

	if (bio)
		bio_list_add(&entry->w_ctx.bios, bio);

	pblk_rb_sync_end(rb, NULL);

	return bio ? 1 : 0;
}