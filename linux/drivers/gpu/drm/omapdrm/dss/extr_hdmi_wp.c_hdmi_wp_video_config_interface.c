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
struct videomode {int flags; } ;
struct hdmi_wp_data {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int DISPLAY_FLAGS_HSYNC_LOW ; 
 int DISPLAY_FLAGS_INTERLACED ; 
 int DISPLAY_FLAGS_VSYNC_LOW ; 
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  HDMI_WP_VIDEO_CFG ; 
 int /*<<< orphan*/  hdmi_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hdmi_wp_video_config_interface(struct hdmi_wp_data *wp,
				    const struct videomode *vm)
{
	u32 r;
	bool vsync_inv, hsync_inv;
	DSSDBG("Enter hdmi_wp_video_config_interface\n");

	vsync_inv = !!(vm->flags & DISPLAY_FLAGS_VSYNC_LOW);
	hsync_inv = !!(vm->flags & DISPLAY_FLAGS_HSYNC_LOW);

	r = hdmi_read_reg(wp->base, HDMI_WP_VIDEO_CFG);
	r = FLD_MOD(r, 1, 7, 7);	/* VSYNC_POL to dispc active high */
	r = FLD_MOD(r, 1, 6, 6);	/* HSYNC_POL to dispc active high */
	r = FLD_MOD(r, vsync_inv, 5, 5);	/* CORE_VSYNC_INV */
	r = FLD_MOD(r, hsync_inv, 4, 4);	/* CORE_HSYNC_INV */
	r = FLD_MOD(r, !!(vm->flags & DISPLAY_FLAGS_INTERLACED), 3, 3);
	r = FLD_MOD(r, 1, 1, 0); /* HDMI_TIMING_MASTER_24BIT */
	hdmi_write_reg(wp->base, HDMI_WP_VIDEO_CFG, r);
}