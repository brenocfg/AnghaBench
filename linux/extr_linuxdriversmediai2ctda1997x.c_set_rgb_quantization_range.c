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
struct v4l2_hdmi_colorimetry {scalar_t__ ycbcr_enc; size_t quantization; int /*<<< orphan*/  colorspace; } ;
struct TYPE_6__ {int /*<<< orphan*/  content_type; int /*<<< orphan*/  colorimetry; int /*<<< orphan*/  colorspace; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; } ;
struct TYPE_5__ {TYPE_1__ bt; } ;
struct tda1997x_state {int rgb_quantization_range; TYPE_3__ avi_infoframe; int /*<<< orphan*/  client; TYPE_2__ timings; struct v4l2_hdmi_colorimetry colorimetry; } ;

/* Variables and functions */
#define  V4L2_DV_RGB_RANGE_FULL 129 
#define  V4L2_DV_RGB_RANGE_LIMITED 128 
 size_t V4L2_QUANTIZATION_FULL_RANGE ; 
 size_t V4L2_QUANTIZATION_LIM_RANGE ; 
 scalar_t__ V4L2_YCBCR_ENC_DEFAULT ; 
 int /*<<< orphan*/  debug ; 
 struct v4l2_hdmi_colorimetry v4l2_hdmi_rx_colorimetry (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * v4l2_quantization_names ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_rgb_quantization_range(struct tda1997x_state *state)
{
	struct v4l2_hdmi_colorimetry *c = &state->colorimetry;

	state->colorimetry = v4l2_hdmi_rx_colorimetry(&state->avi_infoframe,
						      NULL,
						      state->timings.bt.height);
	/* If ycbcr_enc is V4L2_YCBCR_ENC_DEFAULT, we receive RGB */
	if (c->ycbcr_enc == V4L2_YCBCR_ENC_DEFAULT) {
		switch (state->rgb_quantization_range) {
		case V4L2_DV_RGB_RANGE_LIMITED:
			c->quantization = V4L2_QUANTIZATION_FULL_RANGE;
			break;
		case V4L2_DV_RGB_RANGE_FULL:
			c->quantization = V4L2_QUANTIZATION_LIM_RANGE;
			break;
		}
	}
	v4l_dbg(1, debug, state->client,
		"colorspace=%d/%d colorimetry=%d range=%s content=%d\n",
		state->avi_infoframe.colorspace, c->colorspace,
		state->avi_infoframe.colorimetry,
		v4l2_quantization_names[c->quantization],
		state->avi_infoframe.content_type);
}