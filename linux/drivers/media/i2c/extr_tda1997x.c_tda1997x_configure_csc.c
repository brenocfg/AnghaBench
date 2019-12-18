#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_hdmi_colorimetry {size_t quantization; int /*<<< orphan*/  colorspace; } ;
struct TYPE_4__ {int height; } ;
struct TYPE_5__ {TYPE_1__ bt; } ;
struct hdmi_avi_infoframe {size_t colorspace; } ;
struct tda1997x_state {size_t vid_fmt; TYPE_3__* conv; int /*<<< orphan*/  client; TYPE_2__ timings; struct v4l2_hdmi_colorimetry colorimetry; struct hdmi_avi_infoframe avi_infoframe; } ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_6__ {int /*<<< orphan*/  offout3; int /*<<< orphan*/  offout2; int /*<<< orphan*/  offout1; int /*<<< orphan*/  p33coef; int /*<<< orphan*/  p32coef; int /*<<< orphan*/  p31coef; int /*<<< orphan*/  p23coef; int /*<<< orphan*/  p22coef; int /*<<< orphan*/  p21coef; int /*<<< orphan*/  p13coef; int /*<<< orphan*/  p12coef; int /*<<< orphan*/  p11coef; int /*<<< orphan*/  offint3; int /*<<< orphan*/  offint2; int /*<<< orphan*/  offint1; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t ITU601_RGBFULL ; 
 size_t ITU709_RGBFULL ; 
#define  OF_FMT_422_CCIR 130 
#define  OF_FMT_422_SMPT 129 
#define  OF_FMT_444 128 
 scalar_t__ REG_BLK_BU ; 
 scalar_t__ REG_BLK_GY ; 
 scalar_t__ REG_BLK_RV ; 
 int /*<<< orphan*/  REG_VDP_CTRL ; 
 scalar_t__ REG_VDP_MATRIX ; 
 size_t RGBFULL_ITU601 ; 
 size_t RGBFULL_ITU709 ; 
 size_t RGBLIMITED_ITU601 ; 
 size_t RGBLIMITED_ITU709 ; 
 size_t RGBLIMITED_RGBFULL ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_REC709 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 size_t V4L2_QUANTIZATION_FULL_RANGE ; 
 size_t V4L2_QUANTIZATION_LIM_RANGE ; 
 int /*<<< orphan*/  VDP_CTRL_MATRIX_BP ; 
 TYPE_3__* conv_matrix ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/ * hdmi_colorspace_names ; 
 int /*<<< orphan*/  io_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_write16 (struct v4l2_subdev*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct tda1997x_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/ * v4l2_quantization_names ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * vidfmt_names ; 

__attribute__((used)) static void
tda1997x_configure_csc(struct v4l2_subdev *sd)
{
	struct tda1997x_state *state = to_state(sd);
	struct hdmi_avi_infoframe *avi = &state->avi_infoframe;
	struct v4l2_hdmi_colorimetry *c = &state->colorimetry;
	/* Blanking code values depend on output colorspace (RGB or YUV) */
	struct blanking_codes {
		s16 code_gy;
		s16 code_bu;
		s16 code_rv;
	};
	static const struct blanking_codes rgb_blanking = { 64, 64, 64 };
	static const struct blanking_codes yuv_blanking = { 64, 512, 512 };
	const struct blanking_codes *blanking_codes = NULL;
	u8 reg;

	v4l_dbg(1, debug, state->client, "input:%s quant:%s output:%s\n",
		hdmi_colorspace_names[avi->colorspace],
		v4l2_quantization_names[c->quantization],
		vidfmt_names[state->vid_fmt]);
	state->conv = NULL;
	switch (state->vid_fmt) {
	/* RGB output */
	case OF_FMT_444:
		blanking_codes = &rgb_blanking;
		if (c->colorspace == V4L2_COLORSPACE_SRGB) {
			if (c->quantization == V4L2_QUANTIZATION_LIM_RANGE)
				state->conv = &conv_matrix[RGBLIMITED_RGBFULL];
		} else {
			if (c->colorspace == V4L2_COLORSPACE_REC709)
				state->conv = &conv_matrix[ITU709_RGBFULL];
			else if (c->colorspace == V4L2_COLORSPACE_SMPTE170M)
				state->conv = &conv_matrix[ITU601_RGBFULL];
		}
		break;

	/* YUV output */
	case OF_FMT_422_SMPT: /* semi-planar */
	case OF_FMT_422_CCIR: /* CCIR656 */
		blanking_codes = &yuv_blanking;
		if ((c->colorspace == V4L2_COLORSPACE_SRGB) &&
		    (c->quantization == V4L2_QUANTIZATION_FULL_RANGE)) {
			if (state->timings.bt.height <= 576)
				state->conv = &conv_matrix[RGBFULL_ITU601];
			else
				state->conv = &conv_matrix[RGBFULL_ITU709];
		} else if ((c->colorspace == V4L2_COLORSPACE_SRGB) &&
			   (c->quantization == V4L2_QUANTIZATION_LIM_RANGE)) {
			if (state->timings.bt.height <= 576)
				state->conv = &conv_matrix[RGBLIMITED_ITU601];
			else
				state->conv = &conv_matrix[RGBLIMITED_ITU709];
		}
		break;
	}

	if (state->conv) {
		v4l_dbg(1, debug, state->client, "%s\n",
			state->conv->name);
		/* enable matrix conversion */
		reg = io_read(sd, REG_VDP_CTRL);
		reg &= ~VDP_CTRL_MATRIX_BP;
		io_write(sd, REG_VDP_CTRL, reg);
		/* offset inputs */
		io_write16(sd, REG_VDP_MATRIX + 0, state->conv->offint1);
		io_write16(sd, REG_VDP_MATRIX + 2, state->conv->offint2);
		io_write16(sd, REG_VDP_MATRIX + 4, state->conv->offint3);
		/* coefficients */
		io_write16(sd, REG_VDP_MATRIX + 6, state->conv->p11coef);
		io_write16(sd, REG_VDP_MATRIX + 8, state->conv->p12coef);
		io_write16(sd, REG_VDP_MATRIX + 10, state->conv->p13coef);
		io_write16(sd, REG_VDP_MATRIX + 12, state->conv->p21coef);
		io_write16(sd, REG_VDP_MATRIX + 14, state->conv->p22coef);
		io_write16(sd, REG_VDP_MATRIX + 16, state->conv->p23coef);
		io_write16(sd, REG_VDP_MATRIX + 18, state->conv->p31coef);
		io_write16(sd, REG_VDP_MATRIX + 20, state->conv->p32coef);
		io_write16(sd, REG_VDP_MATRIX + 22, state->conv->p33coef);
		/* offset outputs */
		io_write16(sd, REG_VDP_MATRIX + 24, state->conv->offout1);
		io_write16(sd, REG_VDP_MATRIX + 26, state->conv->offout2);
		io_write16(sd, REG_VDP_MATRIX + 28, state->conv->offout3);
	} else {
		/* disable matrix conversion */
		reg = io_read(sd, REG_VDP_CTRL);
		reg |= VDP_CTRL_MATRIX_BP;
		io_write(sd, REG_VDP_CTRL, reg);
	}

	/* SetBlankingCodes */
	if (blanking_codes) {
		io_write16(sd, REG_BLK_GY, blanking_codes->code_gy);
		io_write16(sd, REG_BLK_BU, blanking_codes->code_bu);
		io_write16(sd, REG_BLK_RV, blanking_codes->code_rv);
	}
}