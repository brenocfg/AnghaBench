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
struct zfcp_scsi_dev {struct zfcp_port* port; } ;
struct zfcp_port {struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  erp_lock; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int ZFCP_STATUS_COMMON_RUNNING ; 
 int /*<<< orphan*/  ZFCP_STATUS_ERP_NO_REF ; 
 int /*<<< orphan*/  _zfcp_erp_lun_reopen (struct scsi_device*,int,char*,int /*<<< orphan*/ ) ; 
 struct zfcp_scsi_dev* sdev_to_zfcp (struct scsi_device*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zfcp_erp_wait (struct zfcp_adapter*) ; 

void zfcp_erp_lun_shutdown_wait(struct scsi_device *sdev, char *dbftag)
{
	unsigned long flags;
	struct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	struct zfcp_port *port = zfcp_sdev->port;
	struct zfcp_adapter *adapter = port->adapter;
	int clear = ZFCP_STATUS_COMMON_RUNNING | ZFCP_STATUS_COMMON_ERP_FAILED;

	write_lock_irqsave(&adapter->erp_lock, flags);
	_zfcp_erp_lun_reopen(sdev, clear, dbftag, ZFCP_STATUS_ERP_NO_REF);
	write_unlock_irqrestore(&adapter->erp_lock, flags);

	zfcp_erp_wait(adapter);
}