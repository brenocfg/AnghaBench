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
struct videomode {int dummy; } ;
struct omap_overlay_info {int /*<<< orphan*/  rotation_type; int /*<<< orphan*/  global_alpha; int /*<<< orphan*/  pre_mult_alpha; int /*<<< orphan*/  zorder; int /*<<< orphan*/  rotation; int /*<<< orphan*/  fourcc; int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pos_y; int /*<<< orphan*/  pos_x; int /*<<< orphan*/  screen_width; int /*<<< orphan*/  p_uv_addr; int /*<<< orphan*/  paddr; } ;
struct dispc_device {TYPE_1__* feat; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;
typedef  enum omap_overlay_caps { ____Placeholder_omap_overlay_caps } omap_overlay_caps ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_2__ {int* overlay_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const) ; 
 int /*<<< orphan*/  dispc_ovl_set_channel_out (struct dispc_device*,int,int) ; 
 int dispc_ovl_setup_common (struct dispc_device*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,struct videomode const*,int) ; 

__attribute__((used)) static int dispc_ovl_setup(struct dispc_device *dispc,
			   enum omap_plane_id plane,
			   const struct omap_overlay_info *oi,
			   const struct videomode *vm, bool mem_to_mem,
			   enum omap_channel channel)
{
	int r;
	enum omap_overlay_caps caps = dispc->feat->overlay_caps[plane];
	const bool replication = true;

	DSSDBG("dispc_ovl_setup %d, pa %pad, pa_uv %pad, sw %d, %d,%d, %dx%d ->"
		" %dx%d, cmode %x, rot %d, chan %d repl %d\n",
		plane, &oi->paddr, &oi->p_uv_addr, oi->screen_width, oi->pos_x,
		oi->pos_y, oi->width, oi->height, oi->out_width, oi->out_height,
		oi->fourcc, oi->rotation, channel, replication);

	dispc_ovl_set_channel_out(dispc, plane, channel);

	r = dispc_ovl_setup_common(dispc, plane, caps, oi->paddr, oi->p_uv_addr,
		oi->screen_width, oi->pos_x, oi->pos_y, oi->width, oi->height,
		oi->out_width, oi->out_height, oi->fourcc, oi->rotation,
		oi->zorder, oi->pre_mult_alpha, oi->global_alpha,
		oi->rotation_type, replication, vm, mem_to_mem);

	return r;
}