#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sky2_port {unsigned int port; TYPE_1__* netdev; scalar_t__ tx_ring_size; int /*<<< orphan*/  tx_le_map; struct sky2_hw* hw; } ;
struct sky2_hw {scalar_t__ chip_id; scalar_t__ chip_rev; int /*<<< orphan*/  pdev; struct net_device** dev; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2_E_0 ; 
 scalar_t__ CHIP_ID_YUKON_EC_U ; 
 scalar_t__ CHIP_ID_YUKON_EX ; 
 scalar_t__ CHIP_REV_YU_EC_U_A0 ; 
 scalar_t__ CHIP_REV_YU_EX_B0 ; 
 int /*<<< orphan*/  ECU_TXFF_LEV ; 
 int /*<<< orphan*/  F_TX_CHK_AUTO_OFF ; 
 int /*<<< orphan*/  PCI_CAP_ID_PCIX ; 
 scalar_t__ PCI_X_CMD ; 
 int /*<<< orphan*/  PCI_X_CMD_MAX_SPLIT ; 
 int /*<<< orphan*/  Q_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_AL ; 
 int /*<<< orphan*/  Q_TEST ; 
 int /*<<< orphan*/  Q_XS1 ; 
 int /*<<< orphan*/  Q_XS2 ; 
 int /*<<< orphan*/  RB_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_CTRL ; 
 int /*<<< orphan*/  RB_RST_SET ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  netdev_update_features (TYPE_1__*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int pci_find_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rxqaddr ; 
 int /*<<< orphan*/  sky2_mac_init (struct sky2_hw*,unsigned int) ; 
 int /*<<< orphan*/  sky2_pci_read16 (struct sky2_hw*,scalar_t__) ; 
 int /*<<< orphan*/  sky2_pci_write16 (struct sky2_hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_prefetch_init (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sky2_qset (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_ramset (struct sky2_hw*,int /*<<< orphan*/ ,int,int) ; 
 int sky2_read8 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_rx_start (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_vlan_mode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write16 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_init (struct sky2_port*) ; 
 int /*<<< orphan*/ * txqaddr ; 

__attribute__((used)) static void sky2_hw_up(struct sky2_port *sky2)
{
	struct sky2_hw *hw = sky2->hw;
	unsigned port = sky2->port;
	u32 ramsize;
	int cap;
	struct net_device *otherdev = hw->dev[sky2->port^1];

	tx_init(sky2);

	/*
 	 * On dual port PCI-X card, there is an problem where status
	 * can be received out of order due to split transactions
	 */
	if (otherdev && netif_running(otherdev) &&
 	    (cap = pci_find_capability(hw->pdev, PCI_CAP_ID_PCIX))) {
 		u16 cmd;

		cmd = sky2_pci_read16(hw, cap + PCI_X_CMD);
 		cmd &= ~PCI_X_CMD_MAX_SPLIT;
 		sky2_pci_write16(hw, cap + PCI_X_CMD, cmd);
	}

	sky2_mac_init(hw, port);

	/* Register is number of 4K blocks on internal RAM buffer. */
	ramsize = sky2_read8(hw, B2_E_0) * 4;
	if (ramsize > 0) {
		u32 rxspace;

		netdev_dbg(sky2->netdev, "ram buffer %dK\n", ramsize);
		if (ramsize < 16)
			rxspace = ramsize / 2;
		else
			rxspace = 8 + (2*(ramsize - 16))/3;

		sky2_ramset(hw, rxqaddr[port], 0, rxspace);
		sky2_ramset(hw, txqaddr[port], rxspace, ramsize - rxspace);

		/* Make sure SyncQ is disabled */
		sky2_write8(hw, RB_ADDR(port == 0 ? Q_XS1 : Q_XS2, RB_CTRL),
			    RB_RST_SET);
	}

	sky2_qset(hw, txqaddr[port]);

	/* This is copied from sk98lin 10.0.5.3; no one tells me about erratta's */
	if (hw->chip_id == CHIP_ID_YUKON_EX && hw->chip_rev == CHIP_REV_YU_EX_B0)
		sky2_write32(hw, Q_ADDR(txqaddr[port], Q_TEST), F_TX_CHK_AUTO_OFF);

	/* Set almost empty threshold */
	if (hw->chip_id == CHIP_ID_YUKON_EC_U &&
	    hw->chip_rev == CHIP_REV_YU_EC_U_A0)
		sky2_write16(hw, Q_ADDR(txqaddr[port], Q_AL), ECU_TXFF_LEV);

	sky2_prefetch_init(hw, txqaddr[port], sky2->tx_le_map,
			   sky2->tx_ring_size - 1);

	sky2_vlan_mode(sky2->netdev, sky2->netdev->features);
	netdev_update_features(sky2->netdev);

	sky2_rx_start(sky2);
}