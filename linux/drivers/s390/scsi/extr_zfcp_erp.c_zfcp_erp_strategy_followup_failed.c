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
struct zfcp_erp_action {int type; int /*<<< orphan*/  sdev; int /*<<< orphan*/  port; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
#define  ZFCP_ERP_ACTION_REOPEN_ADAPTER 131 
#define  ZFCP_ERP_ACTION_REOPEN_LUN 130 
#define  ZFCP_ERP_ACTION_REOPEN_PORT 129 
#define  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED 128 
 int /*<<< orphan*/  _zfcp_erp_adapter_reopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _zfcp_erp_lun_reopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zfcp_erp_port_forced_reopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _zfcp_erp_port_reopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void zfcp_erp_strategy_followup_failed(struct zfcp_erp_action *act)
{
	switch (act->type) {
	case ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		_zfcp_erp_adapter_reopen(act->adapter, 0, "ersff_1");
		break;
	case ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
		_zfcp_erp_port_forced_reopen(act->port, 0, "ersff_2");
		break;
	case ZFCP_ERP_ACTION_REOPEN_PORT:
		_zfcp_erp_port_reopen(act->port, 0, "ersff_3");
		break;
	case ZFCP_ERP_ACTION_REOPEN_LUN:
		_zfcp_erp_lun_reopen(act->sdev, 0, "ersff_4", 0);
		break;
	}
}