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
struct hdmi_wp_data {int /*<<< orphan*/  base; } ;
struct hdmi_video_format {int /*<<< orphan*/  x_res; int /*<<< orphan*/  y_res; int /*<<< orphan*/  packing_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLD_VAL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  HDMI_WP_VIDEO_CFG ; 
 int /*<<< orphan*/  HDMI_WP_VIDEO_SIZE ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hdmi_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hdmi_wp_video_config_format(struct hdmi_wp_data *wp,
		const struct hdmi_video_format *video_fmt)
{
	u32 l = 0;

	REG_FLD_MOD(wp->base, HDMI_WP_VIDEO_CFG, video_fmt->packing_mode,
		10, 8);

	l |= FLD_VAL(video_fmt->y_res, 31, 16);
	l |= FLD_VAL(video_fmt->x_res, 15, 0);
	hdmi_write_reg(wp->base, HDMI_WP_VIDEO_SIZE, l);
}