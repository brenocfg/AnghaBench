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
struct zfcp_erp_action {int type; int /*<<< orphan*/  port; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
#define  ZFCP_ERP_ACTION_REOPEN_ADAPTER 131 
#define  ZFCP_ERP_ACTION_REOPEN_LUN 130 
#define  ZFCP_ERP_ACTION_REOPEN_PORT 129 
#define  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED 128 
 int /*<<< orphan*/  _zfcp_erp_lun_reopen_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _zfcp_erp_port_reopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _zfcp_erp_port_reopen_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void zfcp_erp_strategy_followup_success(struct zfcp_erp_action *act)
{
	switch (act->type) {
	case ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		_zfcp_erp_port_reopen_all(act->adapter, 0, "ersfs_1");
		break;
	case ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
		_zfcp_erp_port_reopen(act->port, 0, "ersfs_2");
		break;
	case ZFCP_ERP_ACTION_REOPEN_PORT:
		_zfcp_erp_lun_reopen_all(act->port, 0, "ersfs_3");
		break;
	case ZFCP_ERP_ACTION_REOPEN_LUN:
		/* NOP */
		break;
	}
}