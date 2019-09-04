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
typedef  unsigned int u32 ;
struct dsi_data {int module_id; int /*<<< orphan*/  syscon; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int OMAP5_DSI1_LANEENABLE_SHIFT ; 
 unsigned int OMAP5_DSI2_LANEENABLE_SHIFT ; 
 int /*<<< orphan*/  OMAP5_DSIPHY_SYSCON_OFFSET ; 
 unsigned int OMAP5_DSI_LANEENABLE_MASK ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int dsi_omap5_mux_pads(struct dsi_data *dsi, unsigned int lanes)
{
	u32 enable_shift;

	if (dsi->module_id == 0)
		enable_shift = OMAP5_DSI1_LANEENABLE_SHIFT;
	else if (dsi->module_id == 1)
		enable_shift = OMAP5_DSI2_LANEENABLE_SHIFT;
	else
		return -ENODEV;

	return regmap_update_bits(dsi->syscon, OMAP5_DSIPHY_SYSCON_OFFSET,
		OMAP5_DSI_LANEENABLE_MASK << enable_shift,
		lanes << enable_shift);
}