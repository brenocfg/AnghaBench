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
struct msm_drm_private {struct drm_crtc** crtcs; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int crtc_vsync_end; int crtc_vsync_start; int crtc_vtotal; int crtc_vdisplay; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct drm_crtc {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int) ; 
 struct drm_encoder* get_encoder_from_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int mdp5_encoder_get_linecount (struct drm_encoder*) ; 

__attribute__((used)) static bool mdp5_get_scanoutpos(struct drm_device *dev, unsigned int pipe,
				bool in_vblank_irq, int *vpos, int *hpos,
				ktime_t *stime, ktime_t *etime,
				const struct drm_display_mode *mode)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct drm_crtc *crtc;
	struct drm_encoder *encoder;
	int line, vsw, vbp, vactive_start, vactive_end, vfp_end;

	crtc = priv->crtcs[pipe];
	if (!crtc) {
		DRM_ERROR("Invalid crtc %d\n", pipe);
		return false;
	}

	encoder = get_encoder_from_crtc(crtc);
	if (!encoder) {
		DRM_ERROR("no encoder found for crtc %d\n", pipe);
		return false;
	}

	vsw = mode->crtc_vsync_end - mode->crtc_vsync_start;
	vbp = mode->crtc_vtotal - mode->crtc_vsync_end;

	/*
	 * the line counter is 1 at the start of the VSYNC pulse and VTOTAL at
	 * the end of VFP. Translate the porch values relative to the line
	 * counter positions.
	 */

	vactive_start = vsw + vbp + 1;

	vactive_end = vactive_start + mode->crtc_vdisplay;

	/* last scan line before VSYNC */
	vfp_end = mode->crtc_vtotal;

	if (stime)
		*stime = ktime_get();

	line = mdp5_encoder_get_linecount(encoder);

	if (line < vactive_start) {
		line -= vactive_start;
	} else if (line > vactive_end) {
		line = line - vfp_end - vactive_start;
	} else {
		line -= vactive_start;
	}

	*vpos = line;
	*hpos = 0;

	if (etime)
		*etime = ktime_get();

	return true;
}