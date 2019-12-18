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
struct videomode {scalar_t__ vsync_len; scalar_t__ vfront_porch; scalar_t__ vback_porch; scalar_t__ hsync_len; scalar_t__ hfront_porch; scalar_t__ hback_porch; } ;
struct hdmi_wp_data {int version; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  FLD_VAL (scalar_t__,int,int) ; 
 int /*<<< orphan*/  HDMI_WP_VIDEO_TIMING_H ; 
 int /*<<< orphan*/  HDMI_WP_VIDEO_TIMING_V ; 
 int /*<<< orphan*/  hdmi_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hdmi_wp_video_config_timing(struct hdmi_wp_data *wp,
				 const struct videomode *vm)
{
	u32 timing_h = 0;
	u32 timing_v = 0;
	unsigned int hsync_len_offset = 1;

	DSSDBG("Enter hdmi_wp_video_config_timing\n");

	/*
	 * On OMAP4 and OMAP5 ES1 the HSW field is programmed as is. On OMAP5
	 * ES2+ (including DRA7/AM5 SoCs) HSW field is programmed to hsync_len-1.
	 * However, we don't support OMAP5 ES1 at all, so we can just check for
	 * OMAP4 here.
	 */
	if (wp->version == 4)
		hsync_len_offset = 0;

	timing_h |= FLD_VAL(vm->hback_porch, 31, 20);
	timing_h |= FLD_VAL(vm->hfront_porch, 19, 8);
	timing_h |= FLD_VAL(vm->hsync_len - hsync_len_offset, 7, 0);
	hdmi_write_reg(wp->base, HDMI_WP_VIDEO_TIMING_H, timing_h);

	timing_v |= FLD_VAL(vm->vback_porch, 31, 20);
	timing_v |= FLD_VAL(vm->vfront_porch, 19, 8);
	timing_v |= FLD_VAL(vm->vsync_len, 7, 0);
	hdmi_write_reg(wp->base, HDMI_WP_VIDEO_TIMING_V, timing_v);
}