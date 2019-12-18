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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct dispc_device {int dummy; } ;
typedef  enum omap_plane_id { ____Placeholder_omap_plane_id } omap_plane_id ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_COLOR_COMPONENT_RGB_Y ; 
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
 int /*<<< orphan*/  FEAT_LINEBUFFERSPLIT ; 
 int /*<<< orphan*/  FEAT_RESIZECONF ; 
 scalar_t__ dispc_has_feature (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_ovl_set_scale_param (struct dispc_device*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_ovl_set_vid_accu0 (struct dispc_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dispc_ovl_set_vid_accu1 (struct dispc_device*,int,int /*<<< orphan*/ ,int) ; 
 int dispc_read_reg (struct dispc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_write_reg (struct dispc_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dispc_ovl_set_scaling_common(struct dispc_device *dispc,
					 enum omap_plane_id plane,
					 u16 orig_width, u16 orig_height,
					 u16 out_width, u16 out_height,
					 bool ilace, bool five_taps,
					 bool fieldmode, u32 fourcc,
					 u8 rotation)
{
	int accu0 = 0;
	int accu1 = 0;
	u32 l;

	dispc_ovl_set_scale_param(dispc, plane, orig_width, orig_height,
				  out_width, out_height, five_taps,
				  rotation, DISPC_COLOR_COMPONENT_RGB_Y);
	l = dispc_read_reg(dispc, DISPC_OVL_ATTRIBUTES(plane));

	/* RESIZEENABLE and VERTICALTAPS */
	l &= ~((0x3 << 5) | (0x1 << 21));
	l |= (orig_width != out_width) ? (1 << 5) : 0;
	l |= (orig_height != out_height) ? (1 << 6) : 0;
	l |= five_taps ? (1 << 21) : 0;

	/* VRESIZECONF and HRESIZECONF */
	if (dispc_has_feature(dispc, FEAT_RESIZECONF)) {
		l &= ~(0x3 << 7);
		l |= (orig_width <= out_width) ? 0 : (1 << 7);
		l |= (orig_height <= out_height) ? 0 : (1 << 8);
	}

	/* LINEBUFFERSPLIT */
	if (dispc_has_feature(dispc, FEAT_LINEBUFFERSPLIT)) {
		l &= ~(0x1 << 22);
		l |= five_taps ? (1 << 22) : 0;
	}

	dispc_write_reg(dispc, DISPC_OVL_ATTRIBUTES(plane), l);

	/*
	 * field 0 = even field = bottom field
	 * field 1 = odd field = top field
	 */
	if (ilace && !fieldmode) {
		accu1 = 0;
		accu0 = ((1024 * orig_height / out_height) / 2) & 0x3ff;
		if (accu0 >= 1024/2) {
			accu1 = 1024/2;
			accu0 -= accu1;
		}
	}

	dispc_ovl_set_vid_accu0(dispc, plane, 0, accu0);
	dispc_ovl_set_vid_accu1(dispc, plane, 0, accu1);
}