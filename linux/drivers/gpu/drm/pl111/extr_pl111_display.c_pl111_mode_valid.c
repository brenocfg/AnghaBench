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
typedef  int u64 ;
typedef  int u32 ;
struct pl111_drm_dev_private {int memory_bw; TYPE_1__* variant; } ;
struct drm_display_mode {unsigned long long clock; int hdisplay; int vdisplay; int htotal; int vtotal; } ;
struct drm_device {struct pl111_drm_dev_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_2__ {int fb_bpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,int,int,int) ; 
 int MODE_BAD ; 
 int MODE_OK ; 
 int div_u64 (int,int) ; 

__attribute__((used)) static enum drm_mode_status
pl111_mode_valid(struct drm_crtc *crtc,
		 const struct drm_display_mode *mode)
{
	struct drm_device *drm = crtc->dev;
	struct pl111_drm_dev_private *priv = drm->dev_private;
	u32 cpp = priv->variant->fb_bpp / 8;
	u64 bw;

	/*
	 * We use the pixelclock to also account for interlaced modes, the
	 * resulting bandwidth is in bytes per second.
	 */
	bw = mode->clock * 1000ULL; /* In Hz */
	bw = bw * mode->hdisplay * mode->vdisplay * cpp;
	bw = div_u64(bw, mode->htotal * mode->vtotal);

	/*
	 * If no bandwidth constraints, anything goes, else
	 * check if we are too fast.
	 */
	if (priv->memory_bw && (bw > priv->memory_bw)) {
		DRM_DEBUG_KMS("%d x %d @ %d Hz, %d cpp, bw %llu too fast\n",
			      mode->hdisplay, mode->vdisplay,
			      mode->clock * 1000, cpp, bw);

		return MODE_BAD;
	}
	DRM_DEBUG_KMS("%d x %d @ %d Hz, %d cpp, bw %llu bytes/s OK\n",
		      mode->hdisplay, mode->vdisplay,
		      mode->clock * 1000, cpp, bw);

	return MODE_OK;
}