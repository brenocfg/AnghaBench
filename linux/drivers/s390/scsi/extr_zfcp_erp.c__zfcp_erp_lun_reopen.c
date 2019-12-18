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
typedef  int /*<<< orphan*/  u32 ;
struct zfcp_scsi_dev {TYPE_1__* port; } ;
struct zfcp_adapter {int dummy; } ;
struct scsi_device {int dummy; } ;
struct TYPE_2__ {struct zfcp_adapter* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_ERP_ACTION_REOPEN_LUN ; 
 struct zfcp_scsi_dev* sdev_to_zfcp (struct scsi_device*) ; 
 int /*<<< orphan*/  zfcp_erp_action_enqueue (int /*<<< orphan*/ ,struct zfcp_adapter*,TYPE_1__*,struct scsi_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_lun_block (struct scsi_device*,int) ; 

__attribute__((used)) static void _zfcp_erp_lun_reopen(struct scsi_device *sdev, int clear,
				 char *dbftag, u32 act_status)
{
	struct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	struct zfcp_adapter *adapter = zfcp_sdev->port->adapter;

	zfcp_erp_lun_block(sdev, clear);

	zfcp_erp_action_enqueue(ZFCP_ERP_ACTION_REOPEN_LUN, adapter,
				zfcp_sdev->port, sdev, dbftag, act_status);
}