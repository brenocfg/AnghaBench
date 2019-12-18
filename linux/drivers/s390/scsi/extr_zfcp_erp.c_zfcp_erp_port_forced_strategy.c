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
struct zfcp_port {int /*<<< orphan*/  status; } ;
struct zfcp_erp_action {int step; struct zfcp_port* port; } ;
typedef  enum zfcp_erp_act_result { ____Placeholder_zfcp_erp_act_result } zfcp_erp_act_result ;

/* Variables and functions */
 int ZFCP_ERP_FAILED ; 
#define  ZFCP_ERP_STEP_LUN_CLOSING 133 
#define  ZFCP_ERP_STEP_LUN_OPENING 132 
#define  ZFCP_ERP_STEP_PHYS_PORT_CLOSING 131 
#define  ZFCP_ERP_STEP_PORT_CLOSING 130 
#define  ZFCP_ERP_STEP_PORT_OPENING 129 
#define  ZFCP_ERP_STEP_UNINITIALIZED 128 
 int ZFCP_ERP_SUCCEEDED ; 
 int ZFCP_STATUS_COMMON_OPEN ; 
 int ZFCP_STATUS_PORT_PHYS_OPEN ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int zfcp_erp_port_forced_strategy_close (struct zfcp_erp_action*) ; 

__attribute__((used)) static enum zfcp_erp_act_result zfcp_erp_port_forced_strategy(
	struct zfcp_erp_action *erp_action)
{
	struct zfcp_port *port = erp_action->port;
	int status = atomic_read(&port->status);

	switch (erp_action->step) {
	case ZFCP_ERP_STEP_UNINITIALIZED:
		if ((status & ZFCP_STATUS_PORT_PHYS_OPEN) &&
		    (status & ZFCP_STATUS_COMMON_OPEN))
			return zfcp_erp_port_forced_strategy_close(erp_action);
		else
			return ZFCP_ERP_FAILED;

	case ZFCP_ERP_STEP_PHYS_PORT_CLOSING:
		if (!(status & ZFCP_STATUS_PORT_PHYS_OPEN))
			return ZFCP_ERP_SUCCEEDED;
		break;
	case ZFCP_ERP_STEP_PORT_CLOSING:
	case ZFCP_ERP_STEP_PORT_OPENING:
	case ZFCP_ERP_STEP_LUN_CLOSING:
	case ZFCP_ERP_STEP_LUN_OPENING:
		/* NOP */
		break;
	}
	return ZFCP_ERP_FAILED;
}