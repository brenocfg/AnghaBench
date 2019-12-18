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
typedef  int /*<<< orphan*/  u8 ;
struct qlcnic_adapter {int /*<<< orphan*/  drv_sds_rings; scalar_t__ max_sds_rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_RX_QUEUE ; 
 int /*<<< orphan*/  qlcnic_max_rings (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qlcnic_set_sds_ring_count(struct qlcnic_adapter *adapter, u8 rx_cnt)
{
	/* 83xx adapter does not have max_sds_rings intialized in probe */
	if (adapter->max_sds_rings)
		adapter->drv_sds_rings = qlcnic_max_rings(adapter, rx_cnt,
							  QLCNIC_RX_QUEUE);
	else
		adapter->drv_sds_rings = rx_cnt;
}