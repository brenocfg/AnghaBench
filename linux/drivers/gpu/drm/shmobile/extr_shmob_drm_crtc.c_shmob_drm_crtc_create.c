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
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dpms; struct drm_crtc crtc; } ;
struct shmob_drm_device {int /*<<< orphan*/  ddev; TYPE_1__ crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  crtc_funcs ; 
 int /*<<< orphan*/  crtc_helper_funcs ; 
 int /*<<< orphan*/  drm_crtc_helper_add (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int drm_crtc_init (int /*<<< orphan*/ ,struct drm_crtc*,int /*<<< orphan*/ *) ; 

int shmob_drm_crtc_create(struct shmob_drm_device *sdev)
{
	struct drm_crtc *crtc = &sdev->crtc.crtc;
	int ret;

	sdev->crtc.dpms = DRM_MODE_DPMS_OFF;

	ret = drm_crtc_init(sdev->ddev, crtc, &crtc_funcs);
	if (ret < 0)
		return ret;

	drm_crtc_helper_add(crtc, &crtc_helper_funcs);

	return 0;
}