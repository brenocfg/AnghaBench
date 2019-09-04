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
struct kfd_dbgmgr {scalar_t__ pasid; TYPE_2__* dbgdev; } ;
struct dbg_wave_control_info {TYPE_1__* process; } ;
struct TYPE_4__ {scalar_t__ (* dbgdev_wave_control ) (TYPE_2__*,struct dbg_wave_control_info*) ;} ;
struct TYPE_3__ {scalar_t__ pasid; } ;

/* Variables and functions */
 long EINVAL ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_2__*,struct dbg_wave_control_info*) ; 

long kfd_dbgmgr_wave_control(struct kfd_dbgmgr *pmgr,
				struct dbg_wave_control_info *wac_info)
{
	/* Is the requests coming from the already registered process? */
	if (pmgr->pasid != wac_info->process->pasid) {
		pr_debug("H/W debugger support was not registered for requester pasid %d\n",
				wac_info->process->pasid);
		return -EINVAL;
	}

	return (long) pmgr->dbgdev->dbgdev_wave_control(pmgr->dbgdev, wac_info);
}