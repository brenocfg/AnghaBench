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
struct zfcp_adapter {int /*<<< orphan*/  ref; int /*<<< orphan*/  erp_lock; int /*<<< orphan*/  erp_low_mem_count; int /*<<< orphan*/  erp_total_count; } ;
typedef  enum zfcp_erp_act_result { ____Placeholder_zfcp_erp_act_result } zfcp_erp_act_result ;

/* Variables and functions */
#define  ZFCP_ERP_CONTINUES 133 
#define  ZFCP_ERP_DISMISSED 132 
#define  ZFCP_ERP_EXIT 131 
#define  ZFCP_ERP_FAILED 130 
#define  ZFCP_ERP_NOMEM 129 
#define  ZFCP_ERP_SUCCEEDED 128 
 int ZFCP_STATUS_ERP_DISMISSED ; 
 int ZFCP_STATUS_ERP_LOWMEM ; 
 int ZFCP_STATUS_ERP_TIMEDOUT ; 
 int /*<<< orphan*/  _zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zfcp_adapter_release ; 
 int /*<<< orphan*/  zfcp_erp_action_cleanup (struct zfcp_erp_action*,int) ; 
 int /*<<< orphan*/  zfcp_erp_action_dequeue (struct zfcp_erp_action*) ; 
 int /*<<< orphan*/  zfcp_erp_action_to_running (struct zfcp_erp_action*) ; 
 int /*<<< orphan*/  zfcp_erp_strategy_check_fsfreq (struct zfcp_erp_action*) ; 
 int zfcp_erp_strategy_check_target (struct zfcp_erp_action*,int) ; 
 int zfcp_erp_strategy_do_action (struct zfcp_erp_action*) ; 
 int /*<<< orphan*/  zfcp_erp_strategy_followup_failed (struct zfcp_erp_action*) ; 
 int /*<<< orphan*/  zfcp_erp_strategy_followup_success (struct zfcp_erp_action*) ; 
 int /*<<< orphan*/  zfcp_erp_strategy_memwait (struct zfcp_erp_action*) ; 
 int zfcp_erp_strategy_statechange (struct zfcp_erp_action*,int) ; 

__attribute__((used)) static enum zfcp_erp_act_result zfcp_erp_strategy(
	struct zfcp_erp_action *erp_action)
{
	enum zfcp_erp_act_result result;
	unsigned long flags;
	struct zfcp_adapter *adapter = erp_action->adapter;

	kref_get(&adapter->ref);

	write_lock_irqsave(&adapter->erp_lock, flags);
	zfcp_erp_strategy_check_fsfreq(erp_action);

	if (erp_action->status & ZFCP_STATUS_ERP_DISMISSED) {
		zfcp_erp_action_dequeue(erp_action);
		result = ZFCP_ERP_DISMISSED;
		goto unlock;
	}

	if (erp_action->status & ZFCP_STATUS_ERP_TIMEDOUT) {
		result = ZFCP_ERP_FAILED;
		goto check_target;
	}

	zfcp_erp_action_to_running(erp_action);

	/* no lock to allow for blocking operations */
	write_unlock_irqrestore(&adapter->erp_lock, flags);
	result = zfcp_erp_strategy_do_action(erp_action);
	write_lock_irqsave(&adapter->erp_lock, flags);

	if (erp_action->status & ZFCP_STATUS_ERP_DISMISSED)
		result = ZFCP_ERP_CONTINUES;

	switch (result) {
	case ZFCP_ERP_NOMEM:
		if (!(erp_action->status & ZFCP_STATUS_ERP_LOWMEM)) {
			++adapter->erp_low_mem_count;
			erp_action->status |= ZFCP_STATUS_ERP_LOWMEM;
		}
		if (adapter->erp_total_count == adapter->erp_low_mem_count)
			_zfcp_erp_adapter_reopen(adapter, 0, "erstgy1");
		else {
			zfcp_erp_strategy_memwait(erp_action);
			result = ZFCP_ERP_CONTINUES;
		}
		goto unlock;

	case ZFCP_ERP_CONTINUES:
		if (erp_action->status & ZFCP_STATUS_ERP_LOWMEM) {
			--adapter->erp_low_mem_count;
			erp_action->status &= ~ZFCP_STATUS_ERP_LOWMEM;
		}
		goto unlock;
	case ZFCP_ERP_SUCCEEDED:
	case ZFCP_ERP_FAILED:
	case ZFCP_ERP_EXIT:
	case ZFCP_ERP_DISMISSED:
		/* NOP */
		break;
	}

check_target:
	result = zfcp_erp_strategy_check_target(erp_action, result);
	zfcp_erp_action_dequeue(erp_action);
	result = zfcp_erp_strategy_statechange(erp_action, result);
	if (result == ZFCP_ERP_EXIT)
		goto unlock;
	if (result == ZFCP_ERP_SUCCEEDED)
		zfcp_erp_strategy_followup_success(erp_action);
	if (result == ZFCP_ERP_FAILED)
		zfcp_erp_strategy_followup_failed(erp_action);

 unlock:
	write_unlock_irqrestore(&adapter->erp_lock, flags);

	if (result != ZFCP_ERP_CONTINUES)
		zfcp_erp_action_cleanup(erp_action, result);

	kref_put(&adapter->ref, zfcp_adapter_release);
	return result;
}