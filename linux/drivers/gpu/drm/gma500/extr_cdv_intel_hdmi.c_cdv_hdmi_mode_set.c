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
typedef  int u32 ;
struct mid_intel_hdmi_priv {int /*<<< orphan*/  hdmi_reg; scalar_t__ has_hdmi_audio; } ;
struct gma_encoder {struct mid_intel_hdmi_priv* dev_priv; } ;
struct gma_crtc {int pipe; } ;
struct drm_encoder {struct drm_crtc* crtc; struct drm_device* dev; } ;
struct drm_display_mode {int flags; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int HDMIB_PIPE_B_SELECT ; 
 int HDMI_AUDIO_ENABLE ; 
 int HDMI_HSYNC_ACTIVE_HIGH ; 
 int HDMI_NULL_PACKETS_DURING_VSYNC ; 
 int HDMI_VSYNC_ACTIVE_HIGH ; 
 int /*<<< orphan*/  REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 struct gma_crtc* to_gma_crtc (struct drm_crtc*) ; 
 struct gma_encoder* to_gma_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void cdv_hdmi_mode_set(struct drm_encoder *encoder,
			struct drm_display_mode *mode,
			struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct gma_encoder *gma_encoder = to_gma_encoder(encoder);
	struct mid_intel_hdmi_priv *hdmi_priv = gma_encoder->dev_priv;
	u32 hdmib;
	struct drm_crtc *crtc = encoder->crtc;
	struct gma_crtc *gma_crtc = to_gma_crtc(crtc);

	hdmib = (2 << 10);

	if (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
		hdmib |= HDMI_VSYNC_ACTIVE_HIGH;
	if (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
		hdmib |= HDMI_HSYNC_ACTIVE_HIGH;

	if (gma_crtc->pipe == 1)
		hdmib |= HDMIB_PIPE_B_SELECT;

	if (hdmi_priv->has_hdmi_audio) {
		hdmib |= HDMI_AUDIO_ENABLE;
		hdmib |= HDMI_NULL_PACKETS_DURING_VSYNC;
	}

	REG_WRITE(hdmi_priv->hdmi_reg, hdmib);
	REG_READ(hdmi_priv->hdmi_reg);
}