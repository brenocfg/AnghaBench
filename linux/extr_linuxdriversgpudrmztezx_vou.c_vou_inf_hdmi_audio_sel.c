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
struct zx_vou_hw {scalar_t__ vouctl; } ;
struct zx_crtc {struct zx_vou_hw* vou; } ;
struct drm_crtc {int dummy; } ;
typedef  enum vou_inf_hdmi_audio { ____Placeholder_vou_inf_hdmi_audio } vou_inf_hdmi_audio ;

/* Variables and functions */
 int /*<<< orphan*/  VOU_HDMI_AUD_MASK ; 
 scalar_t__ VOU_INF_HDMI_CTRL ; 
 struct zx_crtc* to_zx_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  zx_writel_mask (scalar_t__,int /*<<< orphan*/ ,int) ; 

void vou_inf_hdmi_audio_sel(struct drm_crtc *crtc,
			    enum vou_inf_hdmi_audio aud)
{
	struct zx_crtc *zcrtc = to_zx_crtc(crtc);
	struct zx_vou_hw *vou = zcrtc->vou;

	zx_writel_mask(vou->vouctl + VOU_INF_HDMI_CTRL, VOU_HDMI_AUD_MASK, aud);
}