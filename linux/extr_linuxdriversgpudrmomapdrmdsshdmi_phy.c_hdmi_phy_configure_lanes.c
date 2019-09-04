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
struct hdmi_phy_data {int* lane_function; int* lane_polarity; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  HDMI_TXPHY_PAD_CFG_CTRL ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static void hdmi_phy_configure_lanes(struct hdmi_phy_data *phy)
{
	static const u16 pad_cfg_list[] = {
		0x0123,
		0x0132,
		0x0312,
		0x0321,
		0x0231,
		0x0213,
		0x1023,
		0x1032,
		0x3012,
		0x3021,
		0x2031,
		0x2013,
		0x1203,
		0x1302,
		0x3102,
		0x3201,
		0x2301,
		0x2103,
		0x1230,
		0x1320,
		0x3120,
		0x3210,
		0x2310,
		0x2130,
	};

	u16 lane_cfg = 0;
	int i;
	unsigned int lane_cfg_val;
	u16 pol_val = 0;

	for (i = 0; i < 4; ++i)
		lane_cfg |= phy->lane_function[i] << ((3 - i) * 4);

	pol_val |= phy->lane_polarity[0] << 0;
	pol_val |= phy->lane_polarity[1] << 3;
	pol_val |= phy->lane_polarity[2] << 2;
	pol_val |= phy->lane_polarity[3] << 1;

	for (i = 0; i < ARRAY_SIZE(pad_cfg_list); ++i)
		if (pad_cfg_list[i] == lane_cfg)
			break;

	if (WARN_ON(i == ARRAY_SIZE(pad_cfg_list)))
		i = 0;

	lane_cfg_val = i;

	REG_FLD_MOD(phy->base, HDMI_TXPHY_PAD_CFG_CTRL, lane_cfg_val, 26, 22);
	REG_FLD_MOD(phy->base, HDMI_TXPHY_PAD_CFG_CTRL, pol_val, 30, 27);
}