#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zfcp_erp_action {TYPE_2__* adapter; } ;
typedef  enum zfcp_erp_act_result { ____Placeholder_zfcp_erp_act_result } zfcp_erp_act_result ;
struct TYPE_3__ {int /*<<< orphan*/  status_read_req; int /*<<< orphan*/  sr_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  stat_read_buf_num; int /*<<< orphan*/  stat_miss; TYPE_1__ pool; } ;

/* Variables and functions */
 scalar_t__ ZFCP_ERP_FAILED ; 
 int ZFCP_ERP_SUCCEEDED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mempool_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfcp_erp_adapter_strat_fsf_xconf (struct zfcp_erp_action*) ; 
 scalar_t__ zfcp_erp_adapter_strategy_open_fsf_xport (struct zfcp_erp_action*) ; 
 scalar_t__ zfcp_status_read_refill (TYPE_2__*) ; 

__attribute__((used)) static enum zfcp_erp_act_result zfcp_erp_adapter_strategy_open_fsf(
	struct zfcp_erp_action *act)
{
	if (zfcp_erp_adapter_strat_fsf_xconf(act) == ZFCP_ERP_FAILED)
		return ZFCP_ERP_FAILED;

	if (zfcp_erp_adapter_strategy_open_fsf_xport(act) == ZFCP_ERP_FAILED)
		return ZFCP_ERP_FAILED;

	if (mempool_resize(act->adapter->pool.sr_data,
			   act->adapter->stat_read_buf_num))
		return ZFCP_ERP_FAILED;

	if (mempool_resize(act->adapter->pool.status_read_req,
			   act->adapter->stat_read_buf_num))
		return ZFCP_ERP_FAILED;

	atomic_set(&act->adapter->stat_miss, act->adapter->stat_read_buf_num);
	if (zfcp_status_read_refill(act->adapter))
		return ZFCP_ERP_FAILED;

	return ZFCP_ERP_SUCCEEDED;
}