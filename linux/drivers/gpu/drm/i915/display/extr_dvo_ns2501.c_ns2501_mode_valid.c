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
struct intel_dvo_device {int dummy; } ;
struct drm_display_mode {int hdisplay; int vdisplay; int clock; int /*<<< orphan*/  vtotal; int /*<<< orphan*/  htotal; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int MODE_OK ; 
 int MODE_ONE_SIZE ; 

__attribute__((used)) static enum drm_mode_status ns2501_mode_valid(struct intel_dvo_device *dvo,
					      struct drm_display_mode *mode)
{
	DRM_DEBUG_KMS
	    ("is mode valid (hdisplay=%d,htotal=%d,vdisplay=%d,vtotal=%d)\n",
	     mode->hdisplay, mode->htotal, mode->vdisplay, mode->vtotal);

	/*
	 * Currently, these are all the modes I have data from.
	 * More might exist. Unclear how to find the native resolution
	 * of the panel in here so we could always accept it
	 * by disabling the scaler.
	 */
	if ((mode->hdisplay == 640 && mode->vdisplay == 480 && mode->clock == 25175) ||
	    (mode->hdisplay == 800 && mode->vdisplay == 600 && mode->clock == 40000) ||
	    (mode->hdisplay == 1024 && mode->vdisplay == 768 && mode->clock == 65000)) {
		return MODE_OK;
	} else {
		return MODE_ONE_SIZE;	/* Is this a reasonable error? */
	}
}