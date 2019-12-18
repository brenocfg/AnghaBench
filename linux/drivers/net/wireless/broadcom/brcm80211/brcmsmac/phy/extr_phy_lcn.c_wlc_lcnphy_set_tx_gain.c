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
struct lcnphy_txgains {int gm_gain; int pga_gain; int pad_gain; int /*<<< orphan*/  dac_gain; } ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_enable_tx_gain_override (struct brcms_phy*) ; 
 int wlc_lcnphy_get_pa_gain (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_dac_gain (struct brcms_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wlc_lcnphy_set_tx_gain(struct brcms_phy *pi,
				   struct lcnphy_txgains *target_gains)
{
	u16 pa_gain = wlc_lcnphy_get_pa_gain(pi);

	mod_phy_reg(
		pi, 0x4b5,
		(0xffff << 0),
		((target_gains->gm_gain) |
		 (target_gains->pga_gain << 8)) <<
		0);
	mod_phy_reg(pi, 0x4fb,
		    (0x7fff << 0),
		    ((target_gains->pad_gain) | (pa_gain << 8)) << 0);

	mod_phy_reg(
		pi, 0x4fc,
		(0xffff << 0),
		((target_gains->gm_gain) |
		 (target_gains->pga_gain << 8)) <<
		0);
	mod_phy_reg(pi, 0x4fd,
		    (0x7fff << 0),
		    ((target_gains->pad_gain) | (pa_gain << 8)) << 0);

	wlc_lcnphy_set_dac_gain(pi, target_gains->dac_gain);

	wlc_lcnphy_enable_tx_gain_override(pi);
}