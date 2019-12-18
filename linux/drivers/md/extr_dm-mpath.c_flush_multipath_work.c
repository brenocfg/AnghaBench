#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct multipath {scalar_t__ queue_mode; int /*<<< orphan*/  trigger_event; int /*<<< orphan*/  process_queued_bios; int /*<<< orphan*/  flags; int /*<<< orphan*/  pg_init_in_progress; scalar_t__ hw_handler_name; } ;

/* Variables and functions */
 scalar_t__ DM_TYPE_BIO_BASED ; 
 int /*<<< orphan*/  MPATHF_PG_INIT_DISABLED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmpath_handlerd ; 
 int /*<<< orphan*/  multipath_wait_for_pg_init_completion (struct multipath*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 

__attribute__((used)) static void flush_multipath_work(struct multipath *m)
{
	if (m->hw_handler_name) {
		set_bit(MPATHF_PG_INIT_DISABLED, &m->flags);
		smp_mb__after_atomic();

		if (atomic_read(&m->pg_init_in_progress))
			flush_workqueue(kmpath_handlerd);
		multipath_wait_for_pg_init_completion(m);

		clear_bit(MPATHF_PG_INIT_DISABLED, &m->flags);
		smp_mb__after_atomic();
	}

	if (m->queue_mode == DM_TYPE_BIO_BASED)
		flush_work(&m->process_queued_bios);
	flush_work(&m->trigger_event);
}