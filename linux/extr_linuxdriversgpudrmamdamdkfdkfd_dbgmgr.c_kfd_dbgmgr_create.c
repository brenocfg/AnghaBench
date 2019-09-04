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
struct kfd_dev {TYPE_1__* dqm; int /*<<< orphan*/  init_complete; } ;
struct kfd_dbgmgr {struct kfd_dbgmgr* dbgdev; struct kfd_dev* dev; scalar_t__ pasid; } ;
typedef  enum DBGDEV_TYPE { ____Placeholder_DBGDEV_TYPE } DBGDEV_TYPE ;
struct TYPE_2__ {scalar_t__ sched_policy; } ;

/* Variables and functions */
 int DBGDEV_TYPE_DIQ ; 
 int DBGDEV_TYPE_NODIQ ; 
 scalar_t__ KFD_SCHED_POLICY_NO_HWS ; 
 scalar_t__ WARN_ON (int) ; 
 void* kfd_alloc_struct (struct kfd_dbgmgr*) ; 
 int /*<<< orphan*/  kfd_dbgdev_init (struct kfd_dbgmgr*,struct kfd_dev*,int) ; 
 int /*<<< orphan*/  kfree (struct kfd_dbgmgr*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

bool kfd_dbgmgr_create(struct kfd_dbgmgr **ppmgr, struct kfd_dev *pdev)
{
	enum DBGDEV_TYPE type = DBGDEV_TYPE_DIQ;
	struct kfd_dbgmgr *new_buff;

	if (WARN_ON(!pdev->init_complete))
		return false;

	new_buff = kfd_alloc_struct(new_buff);
	if (!new_buff) {
		pr_err("Failed to allocate dbgmgr instance\n");
		return false;
	}

	new_buff->pasid = 0;
	new_buff->dev = pdev;
	new_buff->dbgdev = kfd_alloc_struct(new_buff->dbgdev);
	if (!new_buff->dbgdev) {
		pr_err("Failed to allocate dbgdev instance\n");
		kfree(new_buff);
		return false;
	}

	/* get actual type of DBGDevice cpsch or not */
	if (pdev->dqm->sched_policy == KFD_SCHED_POLICY_NO_HWS)
		type = DBGDEV_TYPE_NODIQ;

	kfd_dbgdev_init(new_buff->dbgdev, pdev, type);
	*ppmgr = new_buff;

	return true;
}