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
struct pgpath {int dummy; } ;
struct multipath {int /*<<< orphan*/  process_queued_bios; int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  queued_bios; int /*<<< orphan*/  current_pgpath; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_size; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 struct pgpath* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPATHF_PG_INIT_REQUIRED ; 
 int /*<<< orphan*/  MPATHF_QUEUE_IF_NO_PATH ; 
 int /*<<< orphan*/  MPATHF_QUEUE_IO ; 
 struct pgpath* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 struct pgpath* choose_pgpath (struct multipath*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmultipathd ; 
 int /*<<< orphan*/  pg_init_all_paths (struct multipath*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pgpath *__map_bio(struct multipath *m, struct bio *bio)
{
	struct pgpath *pgpath;
	unsigned long flags;
	bool queue_io;

	/* Do we need to select a new pgpath? */
	pgpath = READ_ONCE(m->current_pgpath);
	queue_io = test_bit(MPATHF_QUEUE_IO, &m->flags);
	if (!pgpath || !queue_io)
		pgpath = choose_pgpath(m, bio->bi_iter.bi_size);

	if ((pgpath && queue_io) ||
	    (!pgpath && test_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags))) {
		/* Queue for the daemon to resubmit */
		spin_lock_irqsave(&m->lock, flags);
		bio_list_add(&m->queued_bios, bio);
		spin_unlock_irqrestore(&m->lock, flags);

		/* PG_INIT_REQUIRED cannot be set without QUEUE_IO */
		if (queue_io || test_bit(MPATHF_PG_INIT_REQUIRED, &m->flags))
			pg_init_all_paths(m);
		else if (!queue_io)
			queue_work(kmultipathd, &m->process_queued_bios);

		return ERR_PTR(-EAGAIN);
	}

	return pgpath;
}