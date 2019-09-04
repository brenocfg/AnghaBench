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
struct dispc_device {int dummy; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;
typedef  enum omap_overlay_caps { ____Placeholder_omap_overlay_caps } omap_overlay_caps ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_OVL_POSITION (int) ; 
 int FLD_VAL (int,int,int) ; 
 int OMAP_DSS_OVL_CAP_POS ; 
 int /*<<< orphan*/  dispc_write_reg (struct dispc_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dispc_ovl_set_pos(struct dispc_device *dispc,
			      enum omap_plane_id plane,
			      enum omap_overlay_caps caps, int x, int y)
{
	u32 val;

	if ((caps & OMAP_DSS_OVL_CAP_POS) == 0)
		return;

	val = FLD_VAL(y, 26, 16) | FLD_VAL(x, 10, 0);

	dispc_write_reg(dispc, DISPC_OVL_POSITION(plane), val);
}