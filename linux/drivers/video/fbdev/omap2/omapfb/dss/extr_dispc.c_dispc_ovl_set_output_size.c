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
typedef  int u32 ;
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DISPC_OVL_PICTURE_SIZE (int) ; 
 int /*<<< orphan*/  DISPC_OVL_SIZE (int) ; 
 int FLD_VAL (int,int,int) ; 
 int OMAP_DSS_GFX ; 
 int OMAP_DSS_WB ; 
 int /*<<< orphan*/  dispc_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dispc_ovl_set_output_size(enum omap_plane plane, int width,
		int height)
{
	u32 val;

	BUG_ON(plane == OMAP_DSS_GFX);

	val = FLD_VAL(height - 1, 26, 16) | FLD_VAL(width - 1, 10, 0);

	if (plane == OMAP_DSS_WB)
		dispc_write_reg(DISPC_OVL_PICTURE_SIZE(plane), val);
	else
		dispc_write_reg(DISPC_OVL_SIZE(plane), val);
}