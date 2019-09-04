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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct phy_device {scalar_t__ link; scalar_t__ speed; TYPE_1__ mdio; } ;
struct net_device {struct phy_device* phydev; } ;
struct et131x_adapter {scalar_t__ link; int boot_coma; int registry_jumbo_packet; } ;

/* Variables and functions */
 int ET_PHY_CONFIG_FIFO_DEPTH_32 ; 
 int ET_PHY_CONFIG_TX_FIFO_DEPTH ; 
 int /*<<< orphan*/  PHY_CONFIG ; 
 int /*<<< orphan*/  PHY_DATA_REG ; 
 int /*<<< orphan*/  PHY_INDEX_REG ; 
 int /*<<< orphan*/  PHY_MPHY_CONTROL_REG ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  et1310_config_flow_control (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et1310_config_mac_regs2 (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et1310_disable_phy_coma (struct et131x_adapter*) ; 
 scalar_t__ et1310_in_phy_coma (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_adapter_setup (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_disable_txrx (struct net_device*) ; 
 int /*<<< orphan*/  et131x_enable_txrx (struct net_device*) ; 
 int /*<<< orphan*/  et131x_free_busy_send_packets (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_init_send (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_mii_read (struct et131x_adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  et131x_mii_write (struct et131x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  et131x_set_rx_dma_timer (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_soft_reset (struct et131x_adapter*) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 

__attribute__((used)) static void et131x_adjust_link(struct net_device *netdev)
{
	struct et131x_adapter *adapter = netdev_priv(netdev);
	struct  phy_device *phydev = netdev->phydev;

	if (!phydev)
		return;
	if (phydev->link == adapter->link)
		return;

	/* Check to see if we are in coma mode and if
	 * so, disable it because we will not be able
	 * to read PHY values until we are out.
	 */
	if (et1310_in_phy_coma(adapter))
		et1310_disable_phy_coma(adapter);

	adapter->link = phydev->link;
	phy_print_status(phydev);

	if (phydev->link) {
		adapter->boot_coma = 20;
		if (phydev->speed == SPEED_10) {
			u16 register18;

			et131x_mii_read(adapter, PHY_MPHY_CONTROL_REG,
					&register18);
			et131x_mii_write(adapter, phydev->mdio.addr,
					 PHY_MPHY_CONTROL_REG,
					 register18 | 0x4);
			et131x_mii_write(adapter, phydev->mdio.addr,
					 PHY_INDEX_REG, register18 | 0x8402);
			et131x_mii_write(adapter, phydev->mdio.addr,
					 PHY_DATA_REG, register18 | 511);
			et131x_mii_write(adapter, phydev->mdio.addr,
					 PHY_MPHY_CONTROL_REG, register18);
		}

		et1310_config_flow_control(adapter);

		if (phydev->speed == SPEED_1000 &&
		    adapter->registry_jumbo_packet > 2048) {
			u16 reg;

			et131x_mii_read(adapter, PHY_CONFIG, &reg);
			reg &= ~ET_PHY_CONFIG_TX_FIFO_DEPTH;
			reg |= ET_PHY_CONFIG_FIFO_DEPTH_32;
			et131x_mii_write(adapter, phydev->mdio.addr,
					 PHY_CONFIG, reg);
		}

		et131x_set_rx_dma_timer(adapter);
		et1310_config_mac_regs2(adapter);
	} else {
		adapter->boot_coma = 0;

		if (phydev->speed == SPEED_10) {
			u16 register18;

			et131x_mii_read(adapter, PHY_MPHY_CONTROL_REG,
					&register18);
			et131x_mii_write(adapter, phydev->mdio.addr,
					 PHY_MPHY_CONTROL_REG,
					 register18 | 0x4);
			et131x_mii_write(adapter, phydev->mdio.addr,
					 PHY_INDEX_REG, register18 | 0x8402);
			et131x_mii_write(adapter, phydev->mdio.addr,
					 PHY_DATA_REG, register18 | 511);
			et131x_mii_write(adapter, phydev->mdio.addr,
					 PHY_MPHY_CONTROL_REG, register18);
		}

		et131x_free_busy_send_packets(adapter);
		et131x_init_send(adapter);

		/* Bring the device back to the state it was during
		 * init prior to autonegotiation being complete. This
		 * way, when we get the auto-neg complete interrupt,
		 * we can complete init by calling config_mac_regs2.
		 */
		et131x_soft_reset(adapter);

		et131x_adapter_setup(adapter);

		et131x_disable_txrx(netdev);
		et131x_enable_txrx(netdev);
	}
}