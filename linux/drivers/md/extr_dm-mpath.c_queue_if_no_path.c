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
struct multipath {TYPE_1__* ti; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPATHF_QUEUE_IF_NO_PATH ; 
 int /*<<< orphan*/  MPATHF_SAVED_QUEUE_IF_NO_PATH ; 
 int /*<<< orphan*/  assign_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dm_table_run_md_queue_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_queued_io_list (struct multipath*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int queue_if_no_path(struct multipath *m, bool queue_if_no_path,
			    bool save_old_value)
{
	unsigned long flags;

	spin_lock_irqsave(&m->lock, flags);
	assign_bit(MPATHF_SAVED_QUEUE_IF_NO_PATH, &m->flags,
		   (save_old_value && test_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags)) ||
		   (!save_old_value && queue_if_no_path));
	assign_bit(MPATHF_QUEUE_IF_NO_PATH, &m->flags, queue_if_no_path);
	spin_unlock_irqrestore(&m->lock, flags);

	if (!queue_if_no_path) {
		dm_table_run_md_queue_async(m->ti->table);
		process_queued_io_list(m);
	}

	return 0;
}