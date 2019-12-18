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
struct zfcp_erp_action {int step; int status; struct zfcp_port* port; } ;
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
 int ZFCP_STATUS_COMMON_NOESC ; 
 int ZFCP_STATUS_COMMON_OPEN ; 
 int ZFCP_STATUS_ERP_CLOSE_ONLY ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int zfcp_erp_port_strategy_close (struct zfcp_erp_action*) ; 
 int zfcp_erp_port_strategy_open_common (struct zfcp_erp_action*) ; 

__attribute__((used)) static enum zfcp_erp_act_result zfcp_erp_port_strategy(
	struct zfcp_erp_action *erp_action)
{
	struct zfcp_port *port = erp_action->port;
	int p_status = atomic_read(&port->status);

	if ((p_status & ZFCP_STATUS_COMMON_NOESC) &&
	    !(p_status & ZFCP_STATUS_COMMON_OPEN))
		goto close_init_done;

	switch (erp_action->step) {
	case ZFCP_ERP_STEP_UNINITIALIZED:
		if (p_status & ZFCP_STATUS_COMMON_OPEN)
			return zfcp_erp_port_strategy_close(erp_action);
		break;

	case ZFCP_ERP_STEP_PORT_CLOSING:
		if (p_status & ZFCP_STATUS_COMMON_OPEN)
			return ZFCP_ERP_FAILED;
		break;
	case ZFCP_ERP_STEP_PHYS_PORT_CLOSING:
	case ZFCP_ERP_STEP_PORT_OPENING:
	case ZFCP_ERP_STEP_LUN_CLOSING:
	case ZFCP_ERP_STEP_LUN_OPENING:
		/* NOP */
		break;
	}

close_init_done:
	if (erp_action->status & ZFCP_STATUS_ERP_CLOSE_ONLY)
		return ZFCP_ERP_EXIT;

	return zfcp_erp_port_strategy_open_common(erp_action);
}