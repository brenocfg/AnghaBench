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
struct zfcp_port {int /*<<< orphan*/  status; } ;
struct zfcp_adapter {int /*<<< orphan*/  status; } ;
struct scsi_device {int dummy; } ;
typedef  enum zfcp_erp_act_type { ____Placeholder_zfcp_erp_act_type } zfcp_erp_act_type ;

/* Variables and functions */
#define  ZFCP_ERP_ACTION_REOPEN_ADAPTER 131 
#define  ZFCP_ERP_ACTION_REOPEN_LUN 130 
#define  ZFCP_ERP_ACTION_REOPEN_PORT 129 
#define  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED 128 
 int ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct zfcp_scsi_dev* sdev_to_zfcp (struct scsi_device*) ; 
 int /*<<< orphan*/  zfcp_erp_set_adapter_status (struct zfcp_adapter*,int) ; 
 int /*<<< orphan*/  zfcp_erp_set_port_status (struct zfcp_port*,int) ; 

__attribute__((used)) static enum zfcp_erp_act_type zfcp_erp_handle_failed(
	enum zfcp_erp_act_type want, struct zfcp_adapter *adapter,
	struct zfcp_port *port,	struct scsi_device *sdev)
{
	enum zfcp_erp_act_type need = want;
	struct zfcp_scsi_dev *zsdev;

	switch (want) {
	case ZFCP_ERP_ACTION_REOPEN_LUN:
		zsdev = sdev_to_zfcp(sdev);
		if (atomic_read(&zsdev->status) & ZFCP_STATUS_COMMON_ERP_FAILED)
			need = 0;
		break;
	case ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
		if (atomic_read(&port->status) & ZFCP_STATUS_COMMON_ERP_FAILED)
			need = 0;
		break;
	case ZFCP_ERP_ACTION_REOPEN_PORT:
		if (atomic_read(&port->status) &
		    ZFCP_STATUS_COMMON_ERP_FAILED) {
			need = 0;
			/* ensure propagation of failed status to new devices */
			zfcp_erp_set_port_status(
				port, ZFCP_STATUS_COMMON_ERP_FAILED);
		}
		break;
	case ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		if (atomic_read(&adapter->status) &
		    ZFCP_STATUS_COMMON_ERP_FAILED) {
			need = 0;
			/* ensure propagation of failed status to new devices */
			zfcp_erp_set_adapter_status(
				adapter, ZFCP_STATUS_COMMON_ERP_FAILED);
		}
		break;
	}

	return need;
}