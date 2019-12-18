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
struct pqi_ctrl_info {int /*<<< orphan*/  ctrl_id; TYPE_1__* pci_dev; } ;
typedef  enum pqi_soft_reset_status { ____Placeholder_pqi_soft_reset_status } pqi_soft_reset_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  RESET_ABORT 132 
#define  RESET_INITIATE_DRIVER 131 
#define  RESET_INITIATE_FIRMWARE 130 
#define  RESET_NORESPONSE 129 
#define  RESET_TIMEDOUT 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int pqi_ofa_ctrl_restart (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ofa_ctrl_unquiesce (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ofa_free_host_buffer (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_take_ctrl_offline (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  sis_soft_reset (struct pqi_ctrl_info*) ; 

__attribute__((used)) static void pqi_process_soft_reset(struct pqi_ctrl_info *ctrl_info,
		enum pqi_soft_reset_status reset_status)
{
	int rc;

	switch (reset_status) {
	case RESET_INITIATE_DRIVER:
		/* fall through */
	case RESET_TIMEDOUT:
		dev_info(&ctrl_info->pci_dev->dev,
			"resetting controller %u\n", ctrl_info->ctrl_id);
		sis_soft_reset(ctrl_info);
		/* fall through */
	case RESET_INITIATE_FIRMWARE:
		rc = pqi_ofa_ctrl_restart(ctrl_info);
		pqi_ofa_free_host_buffer(ctrl_info);
		dev_info(&ctrl_info->pci_dev->dev,
			"Online Firmware Activation for controller %u: %s\n",
			ctrl_info->ctrl_id, rc == 0 ? "SUCCESS" : "FAILED");
		break;
	case RESET_ABORT:
		pqi_ofa_ctrl_unquiesce(ctrl_info);
		dev_info(&ctrl_info->pci_dev->dev,
			"Online Firmware Activation for controller %u: %s\n",
			ctrl_info->ctrl_id, "ABORTED");
		break;
	case RESET_NORESPONSE:
		pqi_ofa_free_host_buffer(ctrl_info);
		pqi_take_ctrl_offline(ctrl_info);
		break;
	}
}