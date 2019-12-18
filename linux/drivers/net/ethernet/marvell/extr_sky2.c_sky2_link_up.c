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
struct sky2_port {unsigned int port; scalar_t__ duplex; size_t flow_status; int /*<<< orphan*/  speed; int /*<<< orphan*/  netdev; struct sky2_hw* hw; } ;
struct sky2_hw {int /*<<< orphan*/  watchdog_timer; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
#define  FC_BOTH 131 
#define  FC_NONE 130 
#define  FC_RX 129 
#define  FC_TX 128 
 int LINKLED_BLINK_OFF ; 
 int LINKLED_LINKSYNC_OFF ; 
 int LINKLED_ON ; 
 int /*<<< orphan*/  LNK_LED_REG ; 
 int /*<<< orphan*/  PHY_MARV_INT_MASK ; 
 int /*<<< orphan*/  PHY_M_DEF_MSK ; 
 int /*<<< orphan*/  SK_REG (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gm_phy_write (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct sky2_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  sky2_enable_rx_tx (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_set_ipg (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sky2_link_up(struct sky2_port *sky2)
{
	struct sky2_hw *hw = sky2->hw;
	unsigned port = sky2->port;
	static const char *fc_name[] = {
		[FC_NONE]	= "none",
		[FC_TX]		= "tx",
		[FC_RX]		= "rx",
		[FC_BOTH]	= "both",
	};

	sky2_set_ipg(sky2);

	sky2_enable_rx_tx(sky2);

	gm_phy_write(hw, port, PHY_MARV_INT_MASK, PHY_M_DEF_MSK);

	netif_carrier_on(sky2->netdev);

	mod_timer(&hw->watchdog_timer, jiffies + 1);

	/* Turn on link LED */
	sky2_write8(hw, SK_REG(port, LNK_LED_REG),
		    LINKLED_ON | LINKLED_BLINK_OFF | LINKLED_LINKSYNC_OFF);

	netif_info(sky2, link, sky2->netdev,
		   "Link is up at %d Mbps, %s duplex, flow control %s\n",
		   sky2->speed,
		   sky2->duplex == DUPLEX_FULL ? "full" : "half",
		   fc_name[sky2->flow_status]);
}