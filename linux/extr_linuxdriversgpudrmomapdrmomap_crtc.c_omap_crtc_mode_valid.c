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
typedef  unsigned int uint64_t ;
struct omap_drm_private {unsigned int max_bandwidth; } ;
struct drm_display_mode {int clock; unsigned int hdisplay; unsigned int vdisplay; int htotal; int vtotal; } ;
struct drm_crtc {TYPE_1__* dev; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_2__ {struct omap_drm_private* dev_private; } ;

/* Variables and functions */
 int MODE_BAD ; 
 int MODE_OK ; 
 unsigned int div_u64 (unsigned int,int) ; 

__attribute__((used)) static enum drm_mode_status omap_crtc_mode_valid(struct drm_crtc *crtc,
					const struct drm_display_mode *mode)
{
	struct omap_drm_private *priv = crtc->dev->dev_private;

	/* Check for bandwidth limit */
	if (priv->max_bandwidth) {
		/*
		 * Estimation for the bandwidth need of a given mode with one
		 * full screen plane:
		 * bandwidth = resolution * 32bpp * (pclk / (vtotal * htotal))
		 *					^^ Refresh rate ^^
		 *
		 * The interlaced mode is taken into account by using the
		 * pixelclock in the calculation.
		 *
		 * The equation is rearranged for 64bit arithmetic.
		 */
		uint64_t bandwidth = mode->clock * 1000;
		unsigned int bpp = 4;

		bandwidth = bandwidth * mode->hdisplay * mode->vdisplay * bpp;
		bandwidth = div_u64(bandwidth, mode->htotal * mode->vtotal);

		/*
		 * Reject modes which would need more bandwidth if used with one
		 * full resolution plane (most common use case).
		 */
		if (priv->max_bandwidth < bandwidth)
			return MODE_BAD;
	}

	return MODE_OK;
}