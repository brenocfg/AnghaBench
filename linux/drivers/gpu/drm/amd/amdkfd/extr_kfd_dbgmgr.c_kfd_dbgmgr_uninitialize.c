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
struct kfd_dbgmgr {int /*<<< orphan*/ * dev; scalar_t__ pasid; int /*<<< orphan*/ * dbgdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kfd_dbgmgr_uninitialize(struct kfd_dbgmgr *pmgr)
{
	kfree(pmgr->dbgdev);

	pmgr->dbgdev = NULL;
	pmgr->pasid = 0;
	pmgr->dev = NULL;
}