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
struct zfcp_port {int /*<<< orphan*/  d_id; int /*<<< orphan*/  status; } ;
struct zfcp_erp_action {int step; struct zfcp_port* port; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  scsi_host; } ;
typedef  enum zfcp_erp_act_result { ____Placeholder_zfcp_erp_act_result } zfcp_erp_act_result ;

/* Variables and functions */
 int /*<<< orphan*/  FC_PORTTYPE_PTP ; 
 int ZFCP_ERP_EXIT ; 
 int ZFCP_ERP_FAILED ; 
#define  ZFCP_ERP_STEP_LUN_CLOSING 133 
#define  ZFCP_ERP_STEP_LUN_OPENING 132 
#define  ZFCP_ERP_STEP_PHYS_PORT_CLOSING 131 
#define  ZFCP_ERP_STEP_PORT_CLOSING 130 
#define  ZFCP_ERP_STEP_PORT_OPENING 129 
#define  ZFCP_ERP_STEP_UNINITIALIZED 128 
 int ZFCP_ERP_SUCCEEDED ; 
 int ZFCP_STATUS_COMMON_NOESC ; 
 int ZFCP_STATUS_COMMON_OPEN ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_host_port_type (int /*<<< orphan*/ ) ; 
 int zfcp_erp_open_ptp_port (struct zfcp_erp_action*) ; 
 int zfcp_erp_port_strategy_open_port (struct zfcp_erp_action*) ; 
 int /*<<< orphan*/  zfcp_fc_trigger_did_lookup (struct zfcp_port*) ; 

__attribute__((used)) static enum zfcp_erp_act_result zfcp_erp_port_strategy_open_common(
	struct zfcp_erp_action *act)
{
	struct zfcp_adapter *adapter = act->adapter;
	struct zfcp_port *port = act->port;
	int p_status = atomic_read(&port->status);

	switch (act->step) {
	case ZFCP_ERP_STEP_UNINITIALIZED:
	case ZFCP_ERP_STEP_PHYS_PORT_CLOSING:
	case ZFCP_ERP_STEP_PORT_CLOSING:
		if (fc_host_port_type(adapter->scsi_host) == FC_PORTTYPE_PTP)
			return zfcp_erp_open_ptp_port(act);
		if (!port->d_id) {
			zfcp_fc_trigger_did_lookup(port);
			return ZFCP_ERP_EXIT;
		}
		return zfcp_erp_port_strategy_open_port(act);

	case ZFCP_ERP_STEP_PORT_OPENING:
		/* D_ID might have changed during open */
		if (p_status & ZFCP_STATUS_COMMON_OPEN) {
			if (!port->d_id) {
				zfcp_fc_trigger_did_lookup(port);
				return ZFCP_ERP_EXIT;
			}
			return ZFCP_ERP_SUCCEEDED;
		}
		if (port->d_id && !(p_status & ZFCP_STATUS_COMMON_NOESC)) {
			port->d_id = 0;
			return ZFCP_ERP_FAILED;
		}
		/* no early return otherwise, continue after switch case */
		break;
	case ZFCP_ERP_STEP_LUN_CLOSING:
	case ZFCP_ERP_STEP_LUN_OPENING:
		/* NOP */
		break;
	}
	return ZFCP_ERP_FAILED;
}