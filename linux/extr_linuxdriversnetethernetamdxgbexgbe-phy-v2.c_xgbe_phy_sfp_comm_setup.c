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
struct xgbe_prv_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  pp4; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {unsigned int sfp_mux_address; unsigned int sfp_mux_channel; int /*<<< orphan*/  sfp_comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUX_ADDR_HI ; 
 int /*<<< orphan*/  MUX_ADDR_LO ; 
 int /*<<< orphan*/  MUX_CHAN ; 
 int /*<<< orphan*/  XGBE_SFP_COMM_PCA9545 ; 
 unsigned int XGBE_SFP_DIRECT ; 
 void* XP_GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XP_PROP_4 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ netif_msg_probe (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_phy_sfp_comm_setup(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	unsigned int mux_addr_hi, mux_addr_lo;

	mux_addr_hi = XP_GET_BITS(pdata->pp4, XP_PROP_4, MUX_ADDR_HI);
	mux_addr_lo = XP_GET_BITS(pdata->pp4, XP_PROP_4, MUX_ADDR_LO);
	if (mux_addr_lo == XGBE_SFP_DIRECT)
		return;

	phy_data->sfp_comm = XGBE_SFP_COMM_PCA9545;
	phy_data->sfp_mux_address = (mux_addr_hi << 2) + mux_addr_lo;
	phy_data->sfp_mux_channel = XP_GET_BITS(pdata->pp4, XP_PROP_4,
						MUX_CHAN);

	if (netif_msg_probe(pdata)) {
		dev_dbg(pdata->dev, "SFP: mux_address=%#x\n",
			phy_data->sfp_mux_address);
		dev_dbg(pdata->dev, "SFP: mux_channel=%u\n",
			phy_data->sfp_mux_channel);
	}
}