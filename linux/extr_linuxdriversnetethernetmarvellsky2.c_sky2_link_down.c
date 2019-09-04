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
typedef  int u16 ;
struct sky2_port {unsigned int port; int /*<<< orphan*/  netdev; struct sky2_hw* hw; } ;
struct sky2_hw {int dummy; } ;

/* Variables and functions */
 int GM_GPCR_RX_ENA ; 
 int GM_GPCR_TX_ENA ; 
 int /*<<< orphan*/  GM_GP_CTRL ; 
 int /*<<< orphan*/  LINKLED_OFF ; 
 int /*<<< orphan*/  LNK_LED_REG ; 
 int /*<<< orphan*/  PHY_MARV_INT_MASK ; 
 int /*<<< orphan*/  SK_REG (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gm_phy_write (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gma_read16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct sky2_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sky2_phy_init (struct sky2_hw*,unsigned int) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_link_down(struct sky2_port *sky2)
{
	struct sky2_hw *hw = sky2->hw;
	unsigned port = sky2->port;
	u16 reg;

	gm_phy_write(hw, port, PHY_MARV_INT_MASK, 0);

	reg = gma_read16(hw, port, GM_GP_CTRL);
	reg &= ~(GM_GPCR_RX_ENA | GM_GPCR_TX_ENA);
	gma_write16(hw, port, GM_GP_CTRL, reg);

	netif_carrier_off(sky2->netdev);

	/* Turn off link LED */
	sky2_write8(hw, SK_REG(port, LNK_LED_REG), LINKLED_OFF);

	netif_info(sky2, link, sky2->netdev, "Link is down\n");

	sky2_phy_init(hw, port);
}