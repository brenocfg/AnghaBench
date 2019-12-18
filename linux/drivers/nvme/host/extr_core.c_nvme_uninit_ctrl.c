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
struct nvme_ctrl {int /*<<< orphan*/  device; int /*<<< orphan*/  cdev; int /*<<< orphan*/  fault_inject; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_qos_hide_latency_tolerance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_fault_inject_fini (int /*<<< orphan*/ *) ; 

void nvme_uninit_ctrl(struct nvme_ctrl *ctrl)
{
	nvme_fault_inject_fini(&ctrl->fault_inject);
	dev_pm_qos_hide_latency_tolerance(ctrl->device);
	cdev_device_del(&ctrl->cdev, ctrl->device);
}