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
typedef  int /*<<< orphan*/  u32 ;
struct dispc_device {int dummy; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 int OMAP_DSS_GFX ; 
 int /*<<< orphan*/  dispc_read_reg (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_write_reg (struct dispc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_ovl_set_vid_color_conv(struct dispc_device *dispc,
					 enum omap_plane_id plane, bool enable)
{
	u32 val;

	BUG_ON(plane == OMAP_DSS_GFX);

	val = dispc_read_reg(dispc, DISPC_OVL_ATTRIBUTES(plane));
	val = FLD_MOD(val, enable, 9, 9);
	dispc_write_reg(dispc, DISPC_OVL_ATTRIBUTES(plane), val);
}