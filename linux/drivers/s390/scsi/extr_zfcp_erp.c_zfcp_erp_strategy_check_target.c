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
struct zfcp_port {int dummy; } ;
struct zfcp_erp_action {int type; struct scsi_device* sdev; struct zfcp_port* port; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int dummy; } ;
struct scsi_device {int dummy; } ;
typedef  enum zfcp_erp_act_result { ____Placeholder_zfcp_erp_act_result } zfcp_erp_act_result ;

/* Variables and functions */
#define  ZFCP_ERP_ACTION_REOPEN_ADAPTER 131 
#define  ZFCP_ERP_ACTION_REOPEN_LUN 130 
#define  ZFCP_ERP_ACTION_REOPEN_PORT 129 
#define  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED 128 
 int zfcp_erp_strategy_check_adapter (struct zfcp_adapter*,int) ; 
 int zfcp_erp_strategy_check_lun (struct scsi_device*,int) ; 
 int zfcp_erp_strategy_check_port (struct zfcp_port*,int) ; 

__attribute__((used)) static enum zfcp_erp_act_result zfcp_erp_strategy_check_target(
	struct zfcp_erp_action *erp_action, enum zfcp_erp_act_result result)
{
	struct zfcp_adapter *adapter = erp_action->adapter;
	struct zfcp_port *port = erp_action->port;
	struct scsi_device *sdev = erp_action->sdev;

	switch (erp_action->type) {

	case ZFCP_ERP_ACTION_REOPEN_LUN:
		result = zfcp_erp_strategy_check_lun(sdev, result);
		break;

	case ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
	case ZFCP_ERP_ACTION_REOPEN_PORT:
		result = zfcp_erp_strategy_check_port(port, result);
		break;

	case ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		result = zfcp_erp_strategy_check_adapter(adapter, result);
		break;
	}
	return result;
}