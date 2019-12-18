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
struct zfcp_adapter {int /*<<< orphan*/  scsi_host; int /*<<< orphan*/  status; int /*<<< orphan*/  erp_ready_head; int /*<<< orphan*/  erp_ready_wq; int /*<<< orphan*/  erp_lock; } ;
typedef  enum zfcp_erp_act_result { ____Placeholder_zfcp_erp_act_result } zfcp_erp_act_result ;

/* Variables and functions */
 scalar_t__ FC_PORTTYPE_PTP ; 
 int ZFCP_ERP_FAILED ; 
 int ZFCP_ERP_SUCCEEDED ; 
 int ZFCP_STATUS_ADAPTER_HOST_CON_INIT ; 
 int ZFCP_STATUS_ADAPTER_XCONFIG_OK ; 
 int ZFCP_STATUS_ERP_TIMEDOUT ; 
 int /*<<< orphan*/  atomic_andnot (int,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ fc_host_port_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssleep (int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_action_to_running (struct zfcp_erp_action*) ; 
 int /*<<< orphan*/  zfcp_erp_enqueue_ptp_port (struct zfcp_adapter*) ; 
 scalar_t__ zfcp_fsf_exchange_config_data (struct zfcp_erp_action*) ; 

__attribute__((used)) static enum zfcp_erp_act_result zfcp_erp_adapter_strat_fsf_xconf(
	struct zfcp_erp_action *erp_action)
{
	int retries;
	int sleep = 1;
	struct zfcp_adapter *adapter = erp_action->adapter;

	atomic_andnot(ZFCP_STATUS_ADAPTER_XCONFIG_OK, &adapter->status);

	for (retries = 7; retries; retries--) {
		atomic_andnot(ZFCP_STATUS_ADAPTER_HOST_CON_INIT,
				  &adapter->status);
		write_lock_irq(&adapter->erp_lock);
		zfcp_erp_action_to_running(erp_action);
		write_unlock_irq(&adapter->erp_lock);
		if (zfcp_fsf_exchange_config_data(erp_action)) {
			atomic_andnot(ZFCP_STATUS_ADAPTER_HOST_CON_INIT,
					  &adapter->status);
			return ZFCP_ERP_FAILED;
		}

		wait_event(adapter->erp_ready_wq,
			   !list_empty(&adapter->erp_ready_head));
		if (erp_action->status & ZFCP_STATUS_ERP_TIMEDOUT)
			break;

		if (!(atomic_read(&adapter->status) &
		      ZFCP_STATUS_ADAPTER_HOST_CON_INIT))
			break;

		ssleep(sleep);
		sleep *= 2;
	}

	atomic_andnot(ZFCP_STATUS_ADAPTER_HOST_CON_INIT,
			  &adapter->status);

	if (!(atomic_read(&adapter->status) & ZFCP_STATUS_ADAPTER_XCONFIG_OK))
		return ZFCP_ERP_FAILED;

	if (fc_host_port_type(adapter->scsi_host) == FC_PORTTYPE_PTP)
		zfcp_erp_enqueue_ptp_port(adapter);

	return ZFCP_ERP_SUCCEEDED;
}