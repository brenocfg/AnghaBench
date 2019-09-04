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
typedef  void* u64 ;
struct TYPE_4__ {scalar_t__ alloc_rx_page; scalar_t__ alloc_rx_buff_failed; scalar_t__ alloc_rx_page_failed; scalar_t__ csum_err; } ;
struct ixgbevf_ring {TYPE_2__ rx_stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  vfmprc; int /*<<< orphan*/  last_vfmprc; int /*<<< orphan*/  vfgotc; int /*<<< orphan*/  last_vfgotc; int /*<<< orphan*/  vfgorc; int /*<<< orphan*/  last_vfgorc; int /*<<< orphan*/  vfgptc; int /*<<< orphan*/  last_vfgptc; int /*<<< orphan*/  vfgprc; int /*<<< orphan*/  last_vfgprc; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbevf_adapter {int num_rx_queues; void* alloc_rx_page; void* alloc_rx_buff_failed; void* alloc_rx_page_failed; void* hw_csum_rx_error; struct ixgbevf_ring** rx_ring; TYPE_1__ stats; int /*<<< orphan*/  state; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_VFGORC_LSB ; 
 int /*<<< orphan*/  IXGBE_VFGORC_MSB ; 
 int /*<<< orphan*/  IXGBE_VFGOTC_LSB ; 
 int /*<<< orphan*/  IXGBE_VFGOTC_MSB ; 
 int /*<<< orphan*/  IXGBE_VFGPRC ; 
 int /*<<< orphan*/  IXGBE_VFGPTC ; 
 int /*<<< orphan*/  IXGBE_VFMPRC ; 
 int /*<<< orphan*/  UPDATE_VF_COUNTER_32bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_VF_COUNTER_36bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IXGBEVF_DOWN ; 
 int /*<<< orphan*/  __IXGBEVF_RESETTING ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ixgbevf_update_stats(struct ixgbevf_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u64 alloc_rx_page_failed = 0, alloc_rx_buff_failed = 0;
	u64 alloc_rx_page = 0, hw_csum_rx_error = 0;
	int i;

	if (test_bit(__IXGBEVF_DOWN, &adapter->state) ||
	    test_bit(__IXGBEVF_RESETTING, &adapter->state))
		return;

	UPDATE_VF_COUNTER_32bit(IXGBE_VFGPRC, adapter->stats.last_vfgprc,
				adapter->stats.vfgprc);
	UPDATE_VF_COUNTER_32bit(IXGBE_VFGPTC, adapter->stats.last_vfgptc,
				adapter->stats.vfgptc);
	UPDATE_VF_COUNTER_36bit(IXGBE_VFGORC_LSB, IXGBE_VFGORC_MSB,
				adapter->stats.last_vfgorc,
				adapter->stats.vfgorc);
	UPDATE_VF_COUNTER_36bit(IXGBE_VFGOTC_LSB, IXGBE_VFGOTC_MSB,
				adapter->stats.last_vfgotc,
				adapter->stats.vfgotc);
	UPDATE_VF_COUNTER_32bit(IXGBE_VFMPRC, adapter->stats.last_vfmprc,
				adapter->stats.vfmprc);

	for (i = 0;  i  < adapter->num_rx_queues;  i++) {
		struct ixgbevf_ring *rx_ring = adapter->rx_ring[i];

		hw_csum_rx_error += rx_ring->rx_stats.csum_err;
		alloc_rx_page_failed += rx_ring->rx_stats.alloc_rx_page_failed;
		alloc_rx_buff_failed += rx_ring->rx_stats.alloc_rx_buff_failed;
		alloc_rx_page += rx_ring->rx_stats.alloc_rx_page;
	}

	adapter->hw_csum_rx_error = hw_csum_rx_error;
	adapter->alloc_rx_page_failed = alloc_rx_page_failed;
	adapter->alloc_rx_buff_failed = alloc_rx_buff_failed;
	adapter->alloc_rx_page = alloc_rx_page;
}