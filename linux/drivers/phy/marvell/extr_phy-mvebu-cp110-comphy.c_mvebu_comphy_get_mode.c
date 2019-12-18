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
struct mvebu_comphy_conf {int lane; int port; int mode; int submode; int fw_mode; int mux; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int ARRAY_SIZE (struct mvebu_comphy_conf*) ; 
 int EINVAL ; 
 int PHY_MODE_INVALID ; 
 int PHY_MODE_PCIE ; 
 struct mvebu_comphy_conf* mvebu_comphy_cp110_modes ; 

__attribute__((used)) static int mvebu_comphy_get_mode(bool fw_mode, int lane, int port,
				 enum phy_mode mode, int submode)
{
	int i, n = ARRAY_SIZE(mvebu_comphy_cp110_modes);
	/* Ignore PCIe submode: it represents the width */
	bool ignore_submode = (mode == PHY_MODE_PCIE);
	const struct mvebu_comphy_conf *conf;

	/* Unused PHY mux value is 0x0 */
	if (mode == PHY_MODE_INVALID)
		return 0;

	for (i = 0; i < n; i++) {
		conf = &mvebu_comphy_cp110_modes[i];
		if (conf->lane == lane &&
		    conf->port == port &&
		    conf->mode == mode &&
		    (conf->submode == submode || ignore_submode))
			break;
	}

	if (i == n)
		return -EINVAL;

	if (fw_mode)
		return conf->fw_mode;
	else
		return conf->mux;
}