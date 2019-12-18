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
struct zfcp_erp_action {int status; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  erp_ready_head; int /*<<< orphan*/  erp_ready_wq; int /*<<< orphan*/  erp_lock; } ;
typedef  enum zfcp_erp_act_result { ____Placeholder_zfcp_erp_act_result } zfcp_erp_act_result ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ZFCP_ERP_FAILED ; 
 int ZFCP_ERP_SUCCEEDED ; 
 int ZFCP_STATUS_ERP_TIMEDOUT ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_rec_run (char*,struct zfcp_erp_action*) ; 
 int /*<<< orphan*/  zfcp_erp_action_to_running (struct zfcp_erp_action*) ; 
 int zfcp_fsf_exchange_port_data (struct zfcp_erp_action*) ; 

__attribute__((used)) static enum zfcp_erp_act_result zfcp_erp_adapter_strategy_open_fsf_xport(
	struct zfcp_erp_action *act)
{
	int ret;
	struct zfcp_adapter *adapter = act->adapter;

	write_lock_irq(&adapter->erp_lock);
	zfcp_erp_action_to_running(act);
	write_unlock_irq(&adapter->erp_lock);

	ret = zfcp_fsf_exchange_port_data(act);
	if (ret == -EOPNOTSUPP)
		return ZFCP_ERP_SUCCEEDED;
	if (ret)
		return ZFCP_ERP_FAILED;

	zfcp_dbf_rec_run("erasox1", act);
	wait_event(adapter->erp_ready_wq,
		   !list_empty(&adapter->erp_ready_head));
	zfcp_dbf_rec_run("erasox2", act);
	if (act->status & ZFCP_STATUS_ERP_TIMEDOUT)
		return ZFCP_ERP_FAILED;

	return ZFCP_ERP_SUCCEEDED;
}