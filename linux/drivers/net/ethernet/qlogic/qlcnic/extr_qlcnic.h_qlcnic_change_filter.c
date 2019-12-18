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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct qlcnic_host_tx_ring {int dummy; } ;
struct qlcnic_adapter {TYPE_2__* ahw; } ;
struct TYPE_4__ {TYPE_1__* hw_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* change_l2_filter ) (struct qlcnic_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct qlcnic_host_tx_ring*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct qlcnic_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct qlcnic_host_tx_ring*) ; 

__attribute__((used)) static inline void qlcnic_change_filter(struct qlcnic_adapter *adapter,
					u64 *addr, u16 vlan,
					struct qlcnic_host_tx_ring *tx_ring)
{
	adapter->ahw->hw_ops->change_l2_filter(adapter, addr, vlan, tx_ring);
}