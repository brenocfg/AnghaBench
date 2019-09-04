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
struct atl1c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atl1c_clean_rx_ring (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_clean_tx_ring (struct atl1c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atl1c_trans_high ; 
 int /*<<< orphan*/  atl1c_trans_normal ; 

__attribute__((used)) static void atl1c_reset_dma_ring(struct atl1c_adapter *adapter)
{
	/* release tx-pending skbs and reset tx/rx ring index */
	atl1c_clean_tx_ring(adapter, atl1c_trans_normal);
	atl1c_clean_tx_ring(adapter, atl1c_trans_high);
	atl1c_clean_rx_ring(adapter);
}