#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {int left; int width; int top; int height; } ;
struct ov772x_win_size {int com7_bit; TYPE_1__ rect; } ;
struct ov772x_priv {int /*<<< orphan*/  regmap; TYPE_5__* band_filter_ctrl; int /*<<< orphan*/  fps; TYPE_4__* hflip_ctrl; TYPE_3__* vflip_ctrl; TYPE_2__* info; } ;
struct ov772x_color_format {int dsp3; int dsp4; int com3; int com7; } ;
struct TYPE_10__ {short val; } ;
struct TYPE_9__ {scalar_t__ val; } ;
struct TYPE_8__ {scalar_t__ val; } ;
struct TYPE_7__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDBASE ; 
 int BNDF_ON_OFF ; 
 int /*<<< orphan*/  COM3 ; 
 int /*<<< orphan*/  COM7 ; 
 int /*<<< orphan*/  COM8 ; 
 int /*<<< orphan*/  DSP_CTRL3 ; 
 int /*<<< orphan*/  DSP_CTRL4 ; 
 int /*<<< orphan*/  EXHCH ; 
 int EXHCH_HSIZE_SHIFT ; 
 int EXHCH_VSIZE_SHIFT ; 
 int HFLIP_IMG ; 
 int /*<<< orphan*/  HOUTSIZE ; 
 int /*<<< orphan*/  HREF ; 
 int HREF_HSIZE_SHIFT ; 
 int HREF_HSTART_SHIFT ; 
 int HREF_VSIZE_SHIFT ; 
 int HREF_VSTART_SHIFT ; 
 int /*<<< orphan*/  HSIZE ; 
 int /*<<< orphan*/  HSTART ; 
 int IMG_MASK ; 
 int OV772X_FLAG_HFLIP ; 
 int OV772X_FLAG_VFLIP ; 
 int SWAP_MASK ; 
 int UV_MASK ; 
 int VFLIP_IMG ; 
 int /*<<< orphan*/  VOUTSIZE ; 
 int /*<<< orphan*/  VSIZE ; 
 int /*<<< orphan*/  VSTART ; 
 int ov772x_edgectrl (struct ov772x_priv*) ; 
 int /*<<< orphan*/  ov772x_reset (struct ov772x_priv*) ; 
 int ov772x_set_frame_rate (struct ov772x_priv*,int /*<<< orphan*/ ,struct ov772x_color_format const*,struct ov772x_win_size const*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov772x_set_params(struct ov772x_priv *priv,
			     const struct ov772x_color_format *cfmt,
			     const struct ov772x_win_size *win)
{
	int ret;
	u8  val;

	/* Reset hardware. */
	ov772x_reset(priv);

	/* Edge Ctrl. */
	ret = ov772x_edgectrl(priv);
	if (ret < 0)
		return ret;

	/* Format and window size. */
	ret = regmap_write(priv->regmap, HSTART, win->rect.left >> 2);
	if (ret < 0)
		goto ov772x_set_fmt_error;
	ret = regmap_write(priv->regmap, HSIZE, win->rect.width >> 2);
	if (ret < 0)
		goto ov772x_set_fmt_error;
	ret = regmap_write(priv->regmap, VSTART, win->rect.top >> 1);
	if (ret < 0)
		goto ov772x_set_fmt_error;
	ret = regmap_write(priv->regmap, VSIZE, win->rect.height >> 1);
	if (ret < 0)
		goto ov772x_set_fmt_error;
	ret = regmap_write(priv->regmap, HOUTSIZE, win->rect.width >> 2);
	if (ret < 0)
		goto ov772x_set_fmt_error;
	ret = regmap_write(priv->regmap, VOUTSIZE, win->rect.height >> 1);
	if (ret < 0)
		goto ov772x_set_fmt_error;
	ret = regmap_write(priv->regmap, HREF,
			   ((win->rect.top & 1) << HREF_VSTART_SHIFT) |
			   ((win->rect.left & 3) << HREF_HSTART_SHIFT) |
			   ((win->rect.height & 1) << HREF_VSIZE_SHIFT) |
			   ((win->rect.width & 3) << HREF_HSIZE_SHIFT));
	if (ret < 0)
		goto ov772x_set_fmt_error;
	ret = regmap_write(priv->regmap, EXHCH,
			   ((win->rect.height & 1) << EXHCH_VSIZE_SHIFT) |
			   ((win->rect.width & 3) << EXHCH_HSIZE_SHIFT));
	if (ret < 0)
		goto ov772x_set_fmt_error;

	/* Set DSP_CTRL3. */
	val = cfmt->dsp3;
	if (val) {
		ret = regmap_update_bits(priv->regmap, DSP_CTRL3, UV_MASK, val);
		if (ret < 0)
			goto ov772x_set_fmt_error;
	}

	/* DSP_CTRL4: AEC reference point and DSP output format. */
	if (cfmt->dsp4) {
		ret = regmap_write(priv->regmap, DSP_CTRL4, cfmt->dsp4);
		if (ret < 0)
			goto ov772x_set_fmt_error;
	}

	/* Set COM3. */
	val = cfmt->com3;
	if (priv->info && (priv->info->flags & OV772X_FLAG_VFLIP))
		val |= VFLIP_IMG;
	if (priv->info && (priv->info->flags & OV772X_FLAG_HFLIP))
		val |= HFLIP_IMG;
	if (priv->vflip_ctrl->val)
		val ^= VFLIP_IMG;
	if (priv->hflip_ctrl->val)
		val ^= HFLIP_IMG;

	ret = regmap_update_bits(priv->regmap, COM3, SWAP_MASK | IMG_MASK, val);
	if (ret < 0)
		goto ov772x_set_fmt_error;

	/* COM7: Sensor resolution and output format control. */
	ret = regmap_write(priv->regmap, COM7, win->com7_bit | cfmt->com7);
	if (ret < 0)
		goto ov772x_set_fmt_error;

	/* COM4, CLKRC: Set pixel clock and framerate. */
	ret = ov772x_set_frame_rate(priv, priv->fps, cfmt, win);
	if (ret < 0)
		goto ov772x_set_fmt_error;

	/* Set COM8. */
	if (priv->band_filter_ctrl->val) {
		unsigned short band_filter = priv->band_filter_ctrl->val;

		ret = regmap_update_bits(priv->regmap, COM8,
					 BNDF_ON_OFF, BNDF_ON_OFF);
		if (!ret)
			ret = regmap_update_bits(priv->regmap, BDBASE,
						 0xff, 256 - band_filter);
		if (ret < 0)
			goto ov772x_set_fmt_error;
	}

	return ret;

ov772x_set_fmt_error:

	ov772x_reset(priv);

	return ret;
}