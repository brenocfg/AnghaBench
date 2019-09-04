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
struct kfd_process {scalar_t__ pasid; } ;
struct kfd_dbgmgr {scalar_t__ pasid; TYPE_1__* dbgdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dbgdev_unregister ) (TYPE_1__*) ;} ;

/* Variables and functions */
 long EINVAL ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

long kfd_dbgmgr_unregister(struct kfd_dbgmgr *pmgr, struct kfd_process *p)
{
	/* Is the requests coming from the already registered process? */
	if (pmgr->pasid != p->pasid) {
		pr_debug("H/W debugger is not registered by calling pasid %d\n",
				p->pasid);
		return -EINVAL;
	}

	pmgr->dbgdev->dbgdev_unregister(pmgr->dbgdev);

	pmgr->pasid = 0;

	return 0;
}