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
struct zfcp_scsi_dev {int /*<<< orphan*/  status; } ;
struct zfcp_erp_action {int step; int status; struct scsi_device* sdev; } ;
struct scsi_device {int dummy; } ;
typedef  enum zfcp_erp_act_result { ____Placeholder_zfcp_erp_act_result } zfcp_erp_act_result ;

/* Variables and functions */
 int ZFCP_ERP_EXIT ; 
 int ZFCP_ERP_FAILED ; 
#define  ZFCP_ERP_STEP_LUN_CLOSING 133 
#define  ZFCP_ERP_STEP_LUN_OPENING 132 
#define  ZFCP_ERP_STEP_PHYS_PORT_CLOSING 131 
#define  ZFCP_ERP_STEP_PORT_CLOSING 130 
#define  ZFCP_ERP_STEP_PORT_OPENING 129 
#define  ZFCP_ERP_STEP_UNINITIALIZED 128 
 int ZFCP_ERP_SUCCEEDED ; 
 int ZFCP_STATUS_COMMON_OPEN ; 
 int ZFCP_STATUS_ERP_CLOSE_ONLY ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct zfcp_scsi_dev* sdev_to_zfcp (struct scsi_device*) ; 
 int /*<<< orphan*/  zfcp_erp_lun_strategy_clearstati (struct scsi_device*) ; 
 int zfcp_erp_lun_strategy_close (struct zfcp_erp_action*) ; 
 int zfcp_erp_lun_strategy_open (struct zfcp_erp_action*) ; 

__attribute__((used)) static enum zfcp_erp_act_result zfcp_erp_lun_strategy(
	struct zfcp_erp_action *erp_action)
{
	struct scsi_device *sdev = erp_action->sdev;
	struct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	switch (erp_action->step) {
	case ZFCP_ERP_STEP_UNINITIALIZED:
		zfcp_erp_lun_strategy_clearstati(sdev);
		if (atomic_read(&zfcp_sdev->status) & ZFCP_STATUS_COMMON_OPEN)
			return zfcp_erp_lun_strategy_close(erp_action);
		/* already closed */
		/* fall through */
	case ZFCP_ERP_STEP_LUN_CLOSING:
		if (atomic_read(&zfcp_sdev->status) & ZFCP_STATUS_COMMON_OPEN)
			return ZFCP_ERP_FAILED;
		if (erp_action->status & ZFCP_STATUS_ERP_CLOSE_ONLY)
			return ZFCP_ERP_EXIT;
		return zfcp_erp_lun_strategy_open(erp_action);

	case ZFCP_ERP_STEP_LUN_OPENING:
		if (atomic_read(&zfcp_sdev->status) & ZFCP_STATUS_COMMON_OPEN)
			return ZFCP_ERP_SUCCEEDED;
		break;
	case ZFCP_ERP_STEP_PHYS_PORT_CLOSING:
	case ZFCP_ERP_STEP_PORT_CLOSING:
	case ZFCP_ERP_STEP_PORT_OPENING:
		/* NOP */
		break;
	}
	return ZFCP_ERP_FAILED;
}