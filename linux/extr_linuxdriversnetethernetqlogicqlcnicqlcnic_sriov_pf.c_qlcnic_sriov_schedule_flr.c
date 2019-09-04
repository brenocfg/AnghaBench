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
typedef  int /*<<< orphan*/  work_func_t ;
struct qlcnic_vf_info {int /*<<< orphan*/  flr_work; TYPE_1__* adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  bc_flr_wq; } ;
struct qlcnic_sriov {TYPE_2__ bc; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qlcnic_sriov_schedule_flr(struct qlcnic_sriov *sriov,
				      struct qlcnic_vf_info *vf,
				      work_func_t func)
{
	if (test_bit(__QLCNIC_RESETTING, &vf->adapter->state))
		return;

	INIT_WORK(&vf->flr_work, func);
	queue_work(sriov->bc.bc_flr_wq, &vf->flr_work);
}