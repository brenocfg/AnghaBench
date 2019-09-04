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
struct kfd_process {scalar_t__ pasid; int /*<<< orphan*/  pqm; } ;
struct kfd_dbgmgr {scalar_t__ pasid; TYPE_1__* dbgdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dbgdev_register ) (TYPE_1__*) ;int /*<<< orphan*/ * pqm; } ;

/* Variables and functions */
 long EBUSY ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

long kfd_dbgmgr_register(struct kfd_dbgmgr *pmgr, struct kfd_process *p)
{
	if (pmgr->pasid != 0) {
		pr_debug("H/W debugger is already active using pasid %d\n",
				pmgr->pasid);
		return -EBUSY;
	}

	/* remember pasid */
	pmgr->pasid = p->pasid;

	/* provide the pqm for diq generation */
	pmgr->dbgdev->pqm = &p->pqm;

	/* activate the actual registering */
	pmgr->dbgdev->dbgdev_register(pmgr->dbgdev);

	return 0;
}