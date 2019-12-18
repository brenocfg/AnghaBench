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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_adapter {int drv_tx_rings; int max_rds_rings; int drv_sds_rings; } ;

/* Variables and functions */

__attribute__((used)) static inline int qlcnic_get_ring_regs_len(struct qlcnic_adapter *adapter)
{
	int ring_regs_cnt = (adapter->drv_tx_rings * 5) +
			    (adapter->max_rds_rings * 2) +
			    (adapter->drv_sds_rings * 3) + 5;
	return ring_regs_cnt * sizeof(u32);
}