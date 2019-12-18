#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_4__ {int samplerate; } ;
struct vc4_hdmi {TYPE_2__ audio; struct drm_encoder* encoder; } ;
struct vc4_dev {int dummy; } ;
struct drm_encoder {struct drm_device* dev; struct drm_crtc* crtc; } ;
struct drm_display_mode {int clock; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {TYPE_1__* state; } ;
struct TYPE_3__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VC4_HDMI_CRP_CFG ; 
 int VC4_HDMI_CRP_CFG_EXTERNAL_CTS_EN ; 
 int /*<<< orphan*/  VC4_HDMI_CRP_CFG_N ; 
 int /*<<< orphan*/  VC4_HDMI_CTS_0 ; 
 int /*<<< orphan*/  VC4_HDMI_CTS_1 ; 
 int VC4_SET_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

__attribute__((used)) static void vc4_hdmi_set_n_cts(struct vc4_hdmi *hdmi)
{
	struct drm_encoder *encoder = hdmi->encoder;
	struct drm_crtc *crtc = encoder->crtc;
	struct drm_device *drm = encoder->dev;
	struct vc4_dev *vc4 = to_vc4_dev(drm);
	const struct drm_display_mode *mode = &crtc->state->adjusted_mode;
	u32 samplerate = hdmi->audio.samplerate;
	u32 n, cts;
	u64 tmp;

	n = 128 * samplerate / 1000;
	tmp = (u64)(mode->clock * 1000) * n;
	do_div(tmp, 128 * samplerate);
	cts = tmp;

	HDMI_WRITE(VC4_HDMI_CRP_CFG,
		   VC4_HDMI_CRP_CFG_EXTERNAL_CTS_EN |
		   VC4_SET_FIELD(n, VC4_HDMI_CRP_CFG_N));

	/*
	 * We could get slightly more accurate clocks in some cases by
	 * providing a CTS_1 value.  The two CTS values are alternated
	 * between based on the period fields
	 */
	HDMI_WRITE(VC4_HDMI_CTS_0, cts);
	HDMI_WRITE(VC4_HDMI_CTS_1, cts);
}