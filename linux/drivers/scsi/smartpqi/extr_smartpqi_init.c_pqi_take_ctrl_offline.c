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
struct pqi_ctrl_info {int controller_online; int pqi_mode_enabled; int /*<<< orphan*/  ctrl_offline_work; TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_1__*) ; 
 int /*<<< orphan*/  pqi_ctrl_block_requests (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_disable_ctrl_shutdown ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sis_shutdown_ctrl (struct pqi_ctrl_info*) ; 

__attribute__((used)) static void pqi_take_ctrl_offline(struct pqi_ctrl_info *ctrl_info)
{
	if (!ctrl_info->controller_online)
		return;

	ctrl_info->controller_online = false;
	ctrl_info->pqi_mode_enabled = false;
	pqi_ctrl_block_requests(ctrl_info);
	if (!pqi_disable_ctrl_shutdown)
		sis_shutdown_ctrl(ctrl_info);
	pci_disable_device(ctrl_info->pci_dev);
	dev_err(&ctrl_info->pci_dev->dev, "controller offline\n");
	schedule_work(&ctrl_info->ctrl_offline_work);
}