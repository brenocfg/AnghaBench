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
struct cosm_device {TYPE_1__* hw_ops; } ;
struct TYPE_2__ {scalar_t__ (* ready ) (struct cosm_device*) ;int /*<<< orphan*/  (* reset ) (struct cosm_device*) ;int /*<<< orphan*/  (* force_reset ) (struct cosm_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MIC_READY ; 
 int /*<<< orphan*/  MIC_RESET_FAILED ; 
 int MIC_RESET_TO ; 
 int /*<<< orphan*/  cosm_set_state (struct cosm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct cosm_device*) ; 
 int /*<<< orphan*/  stub2 (struct cosm_device*) ; 
 scalar_t__ stub3 (struct cosm_device*) ; 

__attribute__((used)) static void cosm_hw_reset(struct cosm_device *cdev, bool force)
{
	int i;

#define MIC_RESET_TO (45)
	if (force && cdev->hw_ops->force_reset)
		cdev->hw_ops->force_reset(cdev);
	else
		cdev->hw_ops->reset(cdev);

	for (i = 0; i < MIC_RESET_TO; i++) {
		if (cdev->hw_ops->ready(cdev)) {
			cosm_set_state(cdev, MIC_READY);
			return;
		}
		/*
		 * Resets typically take 10s of seconds to complete.
		 * Since an MMIO read is required to check if the
		 * firmware is ready or not, a 1 second delay works nicely.
		 */
		msleep(1000);
	}
	cosm_set_state(cdev, MIC_RESET_FAILED);
}