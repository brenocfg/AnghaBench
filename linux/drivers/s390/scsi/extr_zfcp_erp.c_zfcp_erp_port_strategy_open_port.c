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
struct zfcp_erp_action {int /*<<< orphan*/  step; } ;
typedef  enum zfcp_erp_act_result { ____Placeholder_zfcp_erp_act_result } zfcp_erp_act_result ;

/* Variables and functions */
 int ENOMEM ; 
 int ZFCP_ERP_CONTINUES ; 
 int ZFCP_ERP_FAILED ; 
 int ZFCP_ERP_NOMEM ; 
 int /*<<< orphan*/  ZFCP_ERP_STEP_PORT_OPENING ; 
 int zfcp_fsf_open_port (struct zfcp_erp_action*) ; 

__attribute__((used)) static enum zfcp_erp_act_result zfcp_erp_port_strategy_open_port(
	struct zfcp_erp_action *erp_action)
{
	int retval;

	retval = zfcp_fsf_open_port(erp_action);
	if (retval == -ENOMEM)
		return ZFCP_ERP_NOMEM;
	erp_action->step = ZFCP_ERP_STEP_PORT_OPENING;
	if (retval)
		return ZFCP_ERP_FAILED;
	return ZFCP_ERP_CONTINUES;
}