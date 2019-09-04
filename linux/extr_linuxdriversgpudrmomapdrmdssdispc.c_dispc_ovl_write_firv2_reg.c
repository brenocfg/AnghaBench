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
 int /*<<< orphan*/  DISPC_OVL_FIR_COEF_V2 (int,int) ; 
 int OMAP_DSS_GFX ; 
 int /*<<< orphan*/  dispc_write_reg (struct dispc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_ovl_write_firv2_reg(struct dispc_device *dispc,
				      enum omap_plane_id plane, int reg,
				      u32 value)
{
	BUG_ON(plane == OMAP_DSS_GFX);

	dispc_write_reg(dispc, DISPC_OVL_FIR_COEF_V2(plane, reg), value);
}