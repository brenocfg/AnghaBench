#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ func; } ;
struct TYPE_3__ {scalar_t__ function; } ;
struct ice_pf {int /*<<< orphan*/  state; TYPE_2__ serv_task; TYPE_1__ serv_tmr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ICE_SERVICE_DIS ; 
 int /*<<< orphan*/  __ICE_SERVICE_SCHED ; 
 int /*<<< orphan*/  cancel_work_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_service_task_stop(struct ice_pf *pf)
{
	set_bit(__ICE_SERVICE_DIS, pf->state);

	if (pf->serv_tmr.function)
		del_timer_sync(&pf->serv_tmr);
	if (pf->serv_task.func)
		cancel_work_sync(&pf->serv_task);

	clear_bit(__ICE_SERVICE_SCHED, pf->state);
}