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
struct skge_port {int port; int /*<<< orphan*/  netdev; struct skge_hw* hw; } ;
struct skge_hw {TYPE_1__** dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  PHY_BCOM_CTRL ; 
 int /*<<< orphan*/  PHY_BCOM_INT_STAT ; 
 int PHY_B_IS_AN_PR ; 
 int PHY_B_IS_LST_CHANGE ; 
 int PHY_B_IS_NO_HDCL ; 
 int PHY_B_IS_PSE ; 
 int PHY_CT_LOOP ; 
 int /*<<< orphan*/  bcom_check_link (struct skge_hw*,int) ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  netif_printk (struct skge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int xm_phy_read (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xm_phy_write (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void bcom_phy_intr(struct skge_port *skge)
{
	struct skge_hw *hw = skge->hw;
	int port = skge->port;
	u16 isrc;

	isrc = xm_phy_read(hw, port, PHY_BCOM_INT_STAT);
	netif_printk(skge, intr, KERN_DEBUG, skge->netdev,
		     "phy interrupt status 0x%x\n", isrc);

	if (isrc & PHY_B_IS_PSE)
		pr_err("%s: uncorrectable pair swap error\n",
		       hw->dev[port]->name);

	/* Workaround BCom Errata:
	 *	enable and disable loopback mode if "NO HCD" occurs.
	 */
	if (isrc & PHY_B_IS_NO_HDCL) {
		u16 ctrl = xm_phy_read(hw, port, PHY_BCOM_CTRL);
		xm_phy_write(hw, port, PHY_BCOM_CTRL,
				  ctrl | PHY_CT_LOOP);
		xm_phy_write(hw, port, PHY_BCOM_CTRL,
				  ctrl & ~PHY_CT_LOOP);
	}

	if (isrc & (PHY_B_IS_AN_PR | PHY_B_IS_LST_CHANGE))
		bcom_check_link(hw, port);

}