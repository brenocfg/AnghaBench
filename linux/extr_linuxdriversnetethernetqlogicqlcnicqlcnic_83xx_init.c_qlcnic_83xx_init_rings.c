#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct qlcnic_adapter {TYPE_1__* ahw; int /*<<< orphan*/  max_sds_rings; int /*<<< orphan*/  max_tx_rings; } ;
struct TYPE_2__ {int /*<<< orphan*/  msix_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_DEF_SDS_RINGS ; 
 int /*<<< orphan*/  QLCNIC_DEF_TX_RINGS ; 
 int /*<<< orphan*/  QLCNIC_MAX_SDS_RINGS ; 
 int /*<<< orphan*/  QLCNIC_MAX_TX_RINGS ; 
 int /*<<< orphan*/  QLCNIC_SINGLE_RING ; 
 int /*<<< orphan*/  qlcnic_set_sds_ring_count (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_set_tx_ring_count (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qlcnic_83xx_init_rings(struct qlcnic_adapter *adapter)
{
	u8 rx_cnt = QLCNIC_DEF_SDS_RINGS;
	u8 tx_cnt = QLCNIC_DEF_TX_RINGS;

	adapter->max_tx_rings = QLCNIC_MAX_TX_RINGS;
	adapter->max_sds_rings = QLCNIC_MAX_SDS_RINGS;

	if (!adapter->ahw->msix_supported) {
		rx_cnt = QLCNIC_SINGLE_RING;
		tx_cnt = QLCNIC_SINGLE_RING;
	}

	/* compute and set drv sds rings */
	qlcnic_set_tx_ring_count(adapter, tx_cnt);
	qlcnic_set_sds_ring_count(adapter, rx_cnt);
}