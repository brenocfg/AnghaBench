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
typedef  int u64 ;
typedef  int u32 ;
struct e1000_tx_desc {int dummy; } ;
struct e1000_hw {int mac_type; scalar_t__ media_type; scalar_t__ bus_type; } ;
struct e1000_adapter {int num_tx_queues; int tx_int_delay; int tx_abs_int_delay; int txd_cmd; int pcix_82544; TYPE_1__* tx_ring; struct e1000_hw hw; } ;
struct TYPE_2__ {int dma; int count; int /*<<< orphan*/  tdt; int /*<<< orphan*/  tdh; } ;

/* Variables and functions */
 int DEFAULT_82542_TIPG_IPGR1 ; 
 int DEFAULT_82542_TIPG_IPGR2 ; 
 int DEFAULT_82542_TIPG_IPGT ; 
 int DEFAULT_82543_TIPG_IPGR1 ; 
 int DEFAULT_82543_TIPG_IPGR2 ; 
 int DEFAULT_82543_TIPG_IPGT_COPPER ; 
 int DEFAULT_82543_TIPG_IPGT_FIBER ; 
 int /*<<< orphan*/  E1000_82542_TDH ; 
 int /*<<< orphan*/  E1000_82542_TDT ; 
 int E1000_COLLISION_THRESHOLD ; 
 int E1000_CT_SHIFT ; 
 int E1000_TCTL_CT ; 
 int E1000_TCTL_PSP ; 
 int E1000_TCTL_RTLC ; 
 int /*<<< orphan*/  E1000_TDH ; 
 int /*<<< orphan*/  E1000_TDT ; 
 int E1000_TIPG_IPGR1_SHIFT ; 
 int E1000_TIPG_IPGR2_SHIFT ; 
 int E1000_TXD_CMD_EOP ; 
 int E1000_TXD_CMD_IDE ; 
 int E1000_TXD_CMD_IFCS ; 
 int E1000_TXD_CMD_RPS ; 
 int E1000_TXD_CMD_RS ; 
 int /*<<< orphan*/  TADV ; 
 int /*<<< orphan*/  TCTL ; 
 int /*<<< orphan*/  TDBAH ; 
 int /*<<< orphan*/  TDBAL ; 
 int /*<<< orphan*/  TDH ; 
 int /*<<< orphan*/  TDLEN ; 
 int /*<<< orphan*/  TDT ; 
 int /*<<< orphan*/  TIDV ; 
 int /*<<< orphan*/  TIPG ; 
 int e1000_82540 ; 
#define  e1000_82542_rev2_0 129 
#define  e1000_82542_rev2_1 128 
 int e1000_82543 ; 
 int e1000_82544 ; 
 scalar_t__ e1000_bus_type_pcix ; 
 int /*<<< orphan*/  e1000_config_collision_dist (struct e1000_hw*) ; 
 scalar_t__ e1000_media_type_fiber ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void e1000_configure_tx(struct e1000_adapter *adapter)
{
	u64 tdba;
	struct e1000_hw *hw = &adapter->hw;
	u32 tdlen, tctl, tipg;
	u32 ipgr1, ipgr2;

	/* Setup the HW Tx Head and Tail descriptor pointers */

	switch (adapter->num_tx_queues) {
	case 1:
	default:
		tdba = adapter->tx_ring[0].dma;
		tdlen = adapter->tx_ring[0].count *
			sizeof(struct e1000_tx_desc);
		ew32(TDLEN, tdlen);
		ew32(TDBAH, (tdba >> 32));
		ew32(TDBAL, (tdba & 0x00000000ffffffffULL));
		ew32(TDT, 0);
		ew32(TDH, 0);
		adapter->tx_ring[0].tdh = ((hw->mac_type >= e1000_82543) ?
					   E1000_TDH : E1000_82542_TDH);
		adapter->tx_ring[0].tdt = ((hw->mac_type >= e1000_82543) ?
					   E1000_TDT : E1000_82542_TDT);
		break;
	}

	/* Set the default values for the Tx Inter Packet Gap timer */
	if ((hw->media_type == e1000_media_type_fiber ||
	     hw->media_type == e1000_media_type_internal_serdes))
		tipg = DEFAULT_82543_TIPG_IPGT_FIBER;
	else
		tipg = DEFAULT_82543_TIPG_IPGT_COPPER;

	switch (hw->mac_type) {
	case e1000_82542_rev2_0:
	case e1000_82542_rev2_1:
		tipg = DEFAULT_82542_TIPG_IPGT;
		ipgr1 = DEFAULT_82542_TIPG_IPGR1;
		ipgr2 = DEFAULT_82542_TIPG_IPGR2;
		break;
	default:
		ipgr1 = DEFAULT_82543_TIPG_IPGR1;
		ipgr2 = DEFAULT_82543_TIPG_IPGR2;
		break;
	}
	tipg |= ipgr1 << E1000_TIPG_IPGR1_SHIFT;
	tipg |= ipgr2 << E1000_TIPG_IPGR2_SHIFT;
	ew32(TIPG, tipg);

	/* Set the Tx Interrupt Delay register */

	ew32(TIDV, adapter->tx_int_delay);
	if (hw->mac_type >= e1000_82540)
		ew32(TADV, adapter->tx_abs_int_delay);

	/* Program the Transmit Control Register */

	tctl = er32(TCTL);
	tctl &= ~E1000_TCTL_CT;
	tctl |= E1000_TCTL_PSP | E1000_TCTL_RTLC |
		(E1000_COLLISION_THRESHOLD << E1000_CT_SHIFT);

	e1000_config_collision_dist(hw);

	/* Setup Transmit Descriptor Settings for eop descriptor */
	adapter->txd_cmd = E1000_TXD_CMD_EOP | E1000_TXD_CMD_IFCS;

	/* only set IDE if we are delaying interrupts using the timers */
	if (adapter->tx_int_delay)
		adapter->txd_cmd |= E1000_TXD_CMD_IDE;

	if (hw->mac_type < e1000_82543)
		adapter->txd_cmd |= E1000_TXD_CMD_RPS;
	else
		adapter->txd_cmd |= E1000_TXD_CMD_RS;

	/* Cache if we're 82544 running in PCI-X because we'll
	 * need this to apply a workaround later in the send path.
	 */
	if (hw->mac_type == e1000_82544 &&
	    hw->bus_type == e1000_bus_type_pcix)
		adapter->pcix_82544 = true;

	ew32(TCTL, tctl);

}