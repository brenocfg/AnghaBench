#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct zfcp_scsi_dev {int /*<<< orphan*/  status; TYPE_3__* port; int /*<<< orphan*/  erp_counter; } ;
struct scsi_device {int dummy; } ;
typedef  enum zfcp_erp_act_result { ____Placeholder_zfcp_erp_act_result } zfcp_erp_act_result ;
struct TYPE_6__ {scalar_t__ wwpn; TYPE_2__* adapter; } ;
struct TYPE_5__ {TYPE_1__* ccw_device; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ZFCP_ERP_CONTINUES 133 
#define  ZFCP_ERP_DISMISSED 132 
#define  ZFCP_ERP_EXIT 131 
#define  ZFCP_ERP_FAILED 130 
#define  ZFCP_ERP_NOMEM 129 
#define  ZFCP_ERP_SUCCEEDED 128 
 int ZFCP_MAX_ERPS ; 
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned long long,unsigned long long) ; 
 struct zfcp_scsi_dev* sdev_to_zfcp (struct scsi_device*) ; 
 int /*<<< orphan*/  zfcp_erp_lun_block (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_lun_unblock (struct scsi_device*) ; 
 int /*<<< orphan*/  zfcp_erp_set_lun_status (struct scsi_device*,int) ; 
 scalar_t__ zfcp_scsi_dev_lun (struct scsi_device*) ; 

__attribute__((used)) static enum zfcp_erp_act_result zfcp_erp_strategy_check_lun(
	struct scsi_device *sdev, enum zfcp_erp_act_result result)
{
	struct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	switch (result) {
	case ZFCP_ERP_SUCCEEDED :
		atomic_set(&zfcp_sdev->erp_counter, 0);
		zfcp_erp_lun_unblock(sdev);
		break;
	case ZFCP_ERP_FAILED :
		atomic_inc(&zfcp_sdev->erp_counter);
		if (atomic_read(&zfcp_sdev->erp_counter) > ZFCP_MAX_ERPS) {
			dev_err(&zfcp_sdev->port->adapter->ccw_device->dev,
				"ERP failed for LUN 0x%016Lx on "
				"port 0x%016Lx\n",
				(unsigned long long)zfcp_scsi_dev_lun(sdev),
				(unsigned long long)zfcp_sdev->port->wwpn);
			zfcp_erp_set_lun_status(sdev,
						ZFCP_STATUS_COMMON_ERP_FAILED);
		}
		break;
	case ZFCP_ERP_CONTINUES:
	case ZFCP_ERP_EXIT:
	case ZFCP_ERP_DISMISSED:
	case ZFCP_ERP_NOMEM:
		/* NOP */
		break;
	}

	if (atomic_read(&zfcp_sdev->status) & ZFCP_STATUS_COMMON_ERP_FAILED) {
		zfcp_erp_lun_block(sdev, 0);
		result = ZFCP_ERP_EXIT;
	}
	return result;
}