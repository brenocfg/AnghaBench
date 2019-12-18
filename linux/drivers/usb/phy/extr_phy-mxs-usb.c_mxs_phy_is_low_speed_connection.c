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
struct mxs_phy {int port_id; int /*<<< orphan*/  regmap_anatop; } ;

/* Variables and functions */
 unsigned int ANADIG_USB1_MISC ; 
 unsigned int ANADIG_USB2_MISC ; 
 unsigned int BM_ANADIG_USB1_MISC_RX_VMIN_FS ; 
 unsigned int BM_ANADIG_USB1_MISC_RX_VPIN_FS ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static bool mxs_phy_is_low_speed_connection(struct mxs_phy *mxs_phy)
{
	unsigned int line_state;
	/* bit definition is the same for all controllers */
	unsigned int dp_bit = BM_ANADIG_USB1_MISC_RX_VPIN_FS,
		     dm_bit = BM_ANADIG_USB1_MISC_RX_VMIN_FS;
	unsigned int reg = ANADIG_USB1_MISC;

	/* If the SoCs don't have anatop, quit */
	if (!mxs_phy->regmap_anatop)
		return false;

	if (mxs_phy->port_id == 0)
		reg = ANADIG_USB1_MISC;
	else if (mxs_phy->port_id == 1)
		reg = ANADIG_USB2_MISC;

	regmap_read(mxs_phy->regmap_anatop, reg, &line_state);

	if ((line_state & (dp_bit | dm_bit)) ==  dm_bit)
		return true;
	else
		return false;
}