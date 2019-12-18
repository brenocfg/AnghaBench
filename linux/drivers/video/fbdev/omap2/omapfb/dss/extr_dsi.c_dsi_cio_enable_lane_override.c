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
typedef  int u8 ;
typedef  int u32 ;
struct platform_device {int dummy; } ;
struct dsi_data {int num_lanes_supported; TYPE_1__* lanes; } ;
struct TYPE_2__ {unsigned int polarity; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_DSIPHY_CFG10 ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct platform_device*,int /*<<< orphan*/ ,int,int,int) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 

__attribute__((used)) static void dsi_cio_enable_lane_override(struct platform_device *dsidev,
		unsigned mask_p, unsigned mask_n)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	int i;
	u32 l;
	u8 lptxscp_start = dsi->num_lanes_supported == 3 ? 22 : 26;

	l = 0;

	for (i = 0; i < dsi->num_lanes_supported; ++i) {
		unsigned p = dsi->lanes[i].polarity;

		if (mask_p & (1 << i))
			l |= 1 << (i * 2 + (p ? 0 : 1));

		if (mask_n & (1 << i))
			l |= 1 << (i * 2 + (p ? 1 : 0));
	}

	/*
	 * Bits in REGLPTXSCPDAT4TO0DXDY:
	 * 17: DY0 18: DX0
	 * 19: DY1 20: DX1
	 * 21: DY2 22: DX2
	 * 23: DY3 24: DX3
	 * 25: DY4 26: DX4
	 */

	/* Set the lane override configuration */

	/* REGLPTXSCPDAT4TO0DXDY */
	REG_FLD_MOD(dsidev, DSI_DSIPHY_CFG10, l, lptxscp_start, 17);

	/* Enable lane override */

	/* ENLPTXSCPDAT */
	REG_FLD_MOD(dsidev, DSI_DSIPHY_CFG10, 1, 27, 27);
}