#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vstats ;
struct TYPE_8__ {scalar_t__ rx_fifo_errors; scalar_t__ rx_nohandler; scalar_t__ tx_carrier_errors; scalar_t__ tx_fifo_errors; scalar_t__ rx_errors; scalar_t__ tx_errors; } ;
struct opa_vnic_stats {TYPE_4__ netstats; scalar_t__ rx_drop_state; scalar_t__ rx_oversize; scalar_t__ rx_runt; scalar_t__ tx_drop_state; scalar_t__ tx_dlid_zero; } ;
struct TYPE_6__ {int /*<<< orphan*/  vesw_id; } ;
struct TYPE_7__ {TYPE_2__ vesw; } ;
struct opa_vnic_adapter {int /*<<< orphan*/  port_num; TYPE_3__ info; int /*<<< orphan*/  vport_num; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  netdev; TYPE_1__* rn_ops; } ;
struct opa_veswport_error_counters {void* rx_logic; void* rx_drop_state; void* rx_oversize; void* rx_runt; void* rx_bad_veswid; void* tx_logic; void* tx_drop_state; void* tx_dlid_zero; void* rx_errors; void* tx_errors; int /*<<< orphan*/  veswport_num; void* vesw_id; void* vp_instance; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* ndo_get_stats64 ) (int /*<<< orphan*/ ,TYPE_4__*) ;} ;

/* Variables and functions */
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct opa_vnic_stats*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__*) ; 

void opa_vnic_get_error_counters(struct opa_vnic_adapter *adapter,
				 struct opa_veswport_error_counters *cntrs)
{
	struct opa_vnic_stats vstats;

	memset(&vstats, 0, sizeof(vstats));
	spin_lock(&adapter->stats_lock);
	adapter->rn_ops->ndo_get_stats64(adapter->netdev, &vstats.netstats);
	spin_unlock(&adapter->stats_lock);

	cntrs->vp_instance = cpu_to_be16(adapter->vport_num);
	cntrs->vesw_id = cpu_to_be16(adapter->info.vesw.vesw_id);
	cntrs->veswport_num = cpu_to_be32(adapter->port_num);

	cntrs->tx_errors = cpu_to_be64(vstats.netstats.tx_errors);
	cntrs->rx_errors = cpu_to_be64(vstats.netstats.rx_errors);
	cntrs->tx_dlid_zero = cpu_to_be64(vstats.tx_dlid_zero);
	cntrs->tx_drop_state = cpu_to_be64(vstats.tx_drop_state);
	cntrs->tx_logic = cpu_to_be64(vstats.netstats.tx_fifo_errors +
				      vstats.netstats.tx_carrier_errors);

	cntrs->rx_bad_veswid = cpu_to_be64(vstats.netstats.rx_nohandler);
	cntrs->rx_runt = cpu_to_be64(vstats.rx_runt);
	cntrs->rx_oversize = cpu_to_be64(vstats.rx_oversize);
	cntrs->rx_drop_state = cpu_to_be64(vstats.rx_drop_state);
	cntrs->rx_logic = cpu_to_be64(vstats.netstats.rx_fifo_errors);
}