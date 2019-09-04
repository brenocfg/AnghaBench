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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct dispc_device {int dummy; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int OMAP_DSS_GFX ; 
 int /*<<< orphan*/  dispc_ovl_set_scaling_common (struct dispc_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_ovl_set_scaling_uv (struct dispc_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_ovl_set_scaling(struct dispc_device *dispc,
				  enum omap_plane_id plane,
				  u16 orig_width, u16 orig_height,
				  u16 out_width, u16 out_height,
				  bool ilace, bool five_taps,
				  bool fieldmode, u32 fourcc,
				  u8 rotation)
{
	BUG_ON(plane == OMAP_DSS_GFX);

	dispc_ovl_set_scaling_common(dispc, plane, orig_width, orig_height,
				     out_width, out_height, ilace, five_taps,
				     fieldmode, fourcc, rotation);

	dispc_ovl_set_scaling_uv(dispc, plane, orig_width, orig_height,
				 out_width, out_height, ilace, five_taps,
				 fieldmode, fourcc, rotation);
}