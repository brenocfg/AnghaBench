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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_format {scalar_t__ which; int /*<<< orphan*/  format; scalar_t__ pad; } ;
struct v4l2_subdev {int dummy; } ;
struct ov7670_win_size {unsigned char com7_bit; TYPE_1__* regs; int /*<<< orphan*/  vstop; int /*<<< orphan*/  vstart; int /*<<< orphan*/  hstop; int /*<<< orphan*/  hstart; } ;
struct ov7670_info {int mbus_config; unsigned char clkrc; struct ov7670_format_struct* fmt; scalar_t__ pclk_hb_disable; } ;
struct ov7670_format_struct {TYPE_1__* regs; } ;
struct TYPE_2__ {unsigned char value; } ;

/* Variables and functions */
 unsigned char COM10_HREF_REV ; 
 unsigned char COM10_PCLK_HB ; 
 unsigned char COM10_VS_NEG ; 
 int EINVAL ; 
 int ENOTTY ; 
 int /*<<< orphan*/  REG_CLKRC ; 
 int /*<<< orphan*/  REG_COM10 ; 
 int /*<<< orphan*/  REG_COM7 ; 
 int V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
 int V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int ov7670_set_hw (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ov7670_try_fmt_internal (struct v4l2_subdev*,int /*<<< orphan*/ *,struct ov7670_format_struct**,struct ov7670_win_size**) ; 
 int ov7670_write (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char) ; 
 int ov7670_write_array (struct v4l2_subdev*,TYPE_1__*) ; 
 struct ov7670_info* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov7670_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct ov7670_format_struct *ovfmt;
	struct ov7670_win_size *wsize;
	struct ov7670_info *info = to_state(sd);
#ifdef CONFIG_VIDEO_V4L2_SUBDEV_API
	struct v4l2_mbus_framefmt *mbus_fmt;
#endif
	unsigned char com7, com10 = 0;
	int ret;

	if (format->pad)
		return -EINVAL;

	if (format->which == V4L2_SUBDEV_FORMAT_TRY) {
		ret = ov7670_try_fmt_internal(sd, &format->format, NULL, NULL);
		if (ret)
			return ret;
#ifdef CONFIG_VIDEO_V4L2_SUBDEV_API
		mbus_fmt = v4l2_subdev_get_try_format(sd, cfg, format->pad);
		*mbus_fmt = format->format;
		return 0;
#else
		return -ENOTTY;
#endif
	}

	ret = ov7670_try_fmt_internal(sd, &format->format, &ovfmt, &wsize);
	if (ret)
		return ret;
	/*
	 * COM7 is a pain in the ass, it doesn't like to be read then
	 * quickly written afterward.  But we have everything we need
	 * to set it absolutely here, as long as the format-specific
	 * register sets list it first.
	 */
	com7 = ovfmt->regs[0].value;
	com7 |= wsize->com7_bit;
	ret = ov7670_write(sd, REG_COM7, com7);
	if (ret)
		return ret;

	/*
	 * Configure the media bus through COM10 register
	 */
	if (info->mbus_config & V4L2_MBUS_VSYNC_ACTIVE_LOW)
		com10 |= COM10_VS_NEG;
	if (info->mbus_config & V4L2_MBUS_HSYNC_ACTIVE_LOW)
		com10 |= COM10_HREF_REV;
	if (info->pclk_hb_disable)
		com10 |= COM10_PCLK_HB;
	ret = ov7670_write(sd, REG_COM10, com10);
	if (ret)
		return ret;

	/*
	 * Now write the rest of the array.  Also store start/stops
	 */
	ret = ov7670_write_array(sd, ovfmt->regs + 1);
	if (ret)
		return ret;

	ret = ov7670_set_hw(sd, wsize->hstart, wsize->hstop, wsize->vstart,
			    wsize->vstop);
	if (ret)
		return ret;

	if (wsize->regs) {
		ret = ov7670_write_array(sd, wsize->regs);
		if (ret)
			return ret;
	}

	info->fmt = ovfmt;

	/*
	 * If we're running RGB565, we must rewrite clkrc after setting
	 * the other parameters or the image looks poor.  If we're *not*
	 * doing RGB565, we must not rewrite clkrc or the image looks
	 * *really* poor.
	 *
	 * (Update) Now that we retain clkrc state, we should be able
	 * to write it unconditionally, and that will make the frame
	 * rate persistent too.
	 */
	ret = ov7670_write(sd, REG_CLKRC, info->clkrc);
	if (ret)
		return ret;

	return 0;
}