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
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_AFE_GAIN_CTRL ; 
 int /*<<< orphan*/  REG_AVID_START_PIXEL_LSB ; 
 int /*<<< orphan*/  REG_AVID_START_PIXEL_MSB ; 
 int /*<<< orphan*/  REG_AVID_STOP_PIXEL_LSB ; 
 int /*<<< orphan*/  REG_AVID_STOP_PIXEL_MSB ; 
 int /*<<< orphan*/  REG_BRIGHTNESS ; 
 int /*<<< orphan*/  REG_CHROMA_CONTROL1 ; 
 int /*<<< orphan*/  REG_CHROMA_CONTROL2 ; 
 int /*<<< orphan*/  REG_CLEAR_LOST_LOCK ; 
 int /*<<< orphan*/  REG_COLOR_KILLER ; 
 int /*<<< orphan*/  REG_COMP_PB_SATURATION ; 
 int /*<<< orphan*/  REG_COMP_PR_SATURATION ; 
 int /*<<< orphan*/  REG_COMP_Y_BRIGHTNESS ; 
 int /*<<< orphan*/  REG_COMP_Y_CONTRAST ; 
 int /*<<< orphan*/  REG_CONTRAST ; 
 int /*<<< orphan*/  REG_HSYNC_START_PIXEL_LSB ; 
 int /*<<< orphan*/  REG_HSYNC_START_PIXEL_MSB ; 
 int /*<<< orphan*/  REG_HSYNC_STOP_PIXEL_LSB ; 
 int /*<<< orphan*/  REG_HSYNC_STOP_PIXEL_MSB ; 
 int /*<<< orphan*/  REG_HUE ; 
 int /*<<< orphan*/  REG_INPUT_SEL ; 
 int /*<<< orphan*/  REG_LUMA_CONTROL1 ; 
 int /*<<< orphan*/  REG_LUMA_CONTROL2 ; 
 int /*<<< orphan*/  REG_LUMA_CONTROL3 ; 
 int /*<<< orphan*/  REG_OPERATION_MODE ; 
 int /*<<< orphan*/  REG_OUTPUT_FORMATTER1 ; 
 int /*<<< orphan*/  REG_OUTPUT_FORMATTER2 ; 
 int /*<<< orphan*/  REG_OUTPUT_FORMATTER3 ; 
 int /*<<< orphan*/  REG_OUTPUT_FORMATTER4 ; 
 int /*<<< orphan*/  REG_OUTPUT_FORMATTER5 ; 
 int /*<<< orphan*/  REG_OUTPUT_FORMATTER6 ; 
 int /*<<< orphan*/  REG_SATURATION ; 
 int /*<<< orphan*/  REG_SYNC_CONTROL ; 
 int /*<<< orphan*/  REG_VBLK_START_LINE_LSB ; 
 int /*<<< orphan*/  REG_VBLK_START_LINE_MSB ; 
 int /*<<< orphan*/  REG_VBLK_STOP_LINE_LSB ; 
 int /*<<< orphan*/  REG_VBLK_STOP_LINE_MSB ; 
 int /*<<< orphan*/  REG_VIDEO_STD ; 
 int /*<<< orphan*/  REG_VSYNC_START_LINE_LSB ; 
 int /*<<< orphan*/  REG_VSYNC_START_LINE_MSB ; 
 int /*<<< orphan*/  REG_VSYNC_STOP_LINE_LSB ; 
 int /*<<< orphan*/  REG_VSYNC_STOP_LINE_MSB ; 
 int /*<<< orphan*/  dump_reg (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tvp514x_reg_dump(struct v4l2_subdev *sd)
{
	dump_reg(sd, REG_INPUT_SEL);
	dump_reg(sd, REG_AFE_GAIN_CTRL);
	dump_reg(sd, REG_VIDEO_STD);
	dump_reg(sd, REG_OPERATION_MODE);
	dump_reg(sd, REG_COLOR_KILLER);
	dump_reg(sd, REG_LUMA_CONTROL1);
	dump_reg(sd, REG_LUMA_CONTROL2);
	dump_reg(sd, REG_LUMA_CONTROL3);
	dump_reg(sd, REG_BRIGHTNESS);
	dump_reg(sd, REG_CONTRAST);
	dump_reg(sd, REG_SATURATION);
	dump_reg(sd, REG_HUE);
	dump_reg(sd, REG_CHROMA_CONTROL1);
	dump_reg(sd, REG_CHROMA_CONTROL2);
	dump_reg(sd, REG_COMP_PR_SATURATION);
	dump_reg(sd, REG_COMP_Y_CONTRAST);
	dump_reg(sd, REG_COMP_PB_SATURATION);
	dump_reg(sd, REG_COMP_Y_BRIGHTNESS);
	dump_reg(sd, REG_AVID_START_PIXEL_LSB);
	dump_reg(sd, REG_AVID_START_PIXEL_MSB);
	dump_reg(sd, REG_AVID_STOP_PIXEL_LSB);
	dump_reg(sd, REG_AVID_STOP_PIXEL_MSB);
	dump_reg(sd, REG_HSYNC_START_PIXEL_LSB);
	dump_reg(sd, REG_HSYNC_START_PIXEL_MSB);
	dump_reg(sd, REG_HSYNC_STOP_PIXEL_LSB);
	dump_reg(sd, REG_HSYNC_STOP_PIXEL_MSB);
	dump_reg(sd, REG_VSYNC_START_LINE_LSB);
	dump_reg(sd, REG_VSYNC_START_LINE_MSB);
	dump_reg(sd, REG_VSYNC_STOP_LINE_LSB);
	dump_reg(sd, REG_VSYNC_STOP_LINE_MSB);
	dump_reg(sd, REG_VBLK_START_LINE_LSB);
	dump_reg(sd, REG_VBLK_START_LINE_MSB);
	dump_reg(sd, REG_VBLK_STOP_LINE_LSB);
	dump_reg(sd, REG_VBLK_STOP_LINE_MSB);
	dump_reg(sd, REG_SYNC_CONTROL);
	dump_reg(sd, REG_OUTPUT_FORMATTER1);
	dump_reg(sd, REG_OUTPUT_FORMATTER2);
	dump_reg(sd, REG_OUTPUT_FORMATTER3);
	dump_reg(sd, REG_OUTPUT_FORMATTER4);
	dump_reg(sd, REG_OUTPUT_FORMATTER5);
	dump_reg(sd, REG_OUTPUT_FORMATTER6);
	dump_reg(sd, REG_CLEAR_LOST_LOCK);
}