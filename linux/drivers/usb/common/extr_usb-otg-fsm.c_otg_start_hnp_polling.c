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
struct otg_fsm {int /*<<< orphan*/  hnp_polling_work; int /*<<< orphan*/  host_req_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_HOST_REQ_POLL ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_hnp_polling_work ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void otg_start_hnp_polling(struct otg_fsm *fsm)
{
	/*
	 * The memory of host_req_flag should be allocated by
	 * controller driver, otherwise, hnp polling is not started.
	 */
	if (!fsm->host_req_flag)
		return;

	INIT_DELAYED_WORK(&fsm->hnp_polling_work, otg_hnp_polling_work);
	schedule_delayed_work(&fsm->hnp_polling_work,
					msecs_to_jiffies(T_HOST_REQ_POLL));
}