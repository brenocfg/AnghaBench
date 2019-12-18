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
struct work_struct {int dummy; } ;
typedef  enum bp_state { ____Placeholder_bp_state } bp_state ;
struct TYPE_2__ {int schedule_delay; } ;

/* Variables and functions */
 int BP_DONE ; 
 int BP_EAGAIN ; 
 int /*<<< orphan*/  GFP_BALLOON ; 
 int HZ ; 
 scalar_t__ balloon_is_inflated () ; 
 int /*<<< orphan*/  balloon_mutex ; 
 TYPE_1__ balloon_stats ; 
 int /*<<< orphan*/  balloon_worker ; 
 int /*<<< orphan*/  cond_resched () ; 
 long current_credit () ; 
 int decrease_reservation (long,int /*<<< orphan*/ ) ; 
 int increase_reservation (long) ; 
 long min (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int reserve_additional_memory () ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  si_mem_available () ; 
 long totalreserve_pages ; 
 int update_schedule (int) ; 

__attribute__((used)) static void balloon_process(struct work_struct *work)
{
	enum bp_state state = BP_DONE;
	long credit;


	do {
		mutex_lock(&balloon_mutex);

		credit = current_credit();

		if (credit > 0) {
			if (balloon_is_inflated())
				state = increase_reservation(credit);
			else
				state = reserve_additional_memory();
		}

		if (credit < 0) {
			long n_pages;

			n_pages = min(-credit, si_mem_available());
			state = decrease_reservation(n_pages, GFP_BALLOON);
			if (state == BP_DONE && n_pages != -credit &&
			    n_pages < totalreserve_pages)
				state = BP_EAGAIN;
		}

		state = update_schedule(state);

		mutex_unlock(&balloon_mutex);

		cond_resched();

	} while (credit && state == BP_DONE);

	/* Schedule more work if there is some still to be done. */
	if (state == BP_EAGAIN)
		schedule_delayed_work(&balloon_worker, balloon_stats.schedule_delay * HZ);
}