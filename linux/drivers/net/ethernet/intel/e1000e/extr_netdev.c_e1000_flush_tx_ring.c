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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct e1000_tx_desc {TYPE_2__ upper; TYPE_1__ lower; int /*<<< orphan*/  buffer_addr; } ;
struct e1000_ring {int next_to_use; int count; int /*<<< orphan*/  dma; } ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {struct e1000_ring* tx_ring; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int E1000_TCTL_EN ; 
 int E1000_TXD_CMD_IFCS ; 
 struct e1000_tx_desc* E1000_TX_DESC (struct e1000_ring,int) ; 
 int /*<<< orphan*/  TCTL ; 
 int /*<<< orphan*/  TDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void e1000_flush_tx_ring(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct e1000_ring *tx_ring = adapter->tx_ring;
	struct e1000_tx_desc *tx_desc = NULL;
	u32 tdt, tctl, txd_lower = E1000_TXD_CMD_IFCS;
	u16 size = 512;

	tctl = er32(TCTL);
	ew32(TCTL, tctl | E1000_TCTL_EN);
	tdt = er32(TDT(0));
	BUG_ON(tdt != tx_ring->next_to_use);
	tx_desc =  E1000_TX_DESC(*tx_ring, tx_ring->next_to_use);
	tx_desc->buffer_addr = tx_ring->dma;

	tx_desc->lower.data = cpu_to_le32(txd_lower | size);
	tx_desc->upper.data = 0;
	/* flush descriptors to memory before notifying the HW */
	wmb();
	tx_ring->next_to_use++;
	if (tx_ring->next_to_use == tx_ring->count)
		tx_ring->next_to_use = 0;
	ew32(TDT(0), tx_ring->next_to_use);
	usleep_range(200, 250);
}