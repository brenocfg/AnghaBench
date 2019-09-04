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
struct shmob_drm_crtc {int dpms; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  shmob_drm_crtc_start (struct shmob_drm_crtc*) ; 
 int /*<<< orphan*/  shmob_drm_crtc_stop (struct shmob_drm_crtc*) ; 
 struct shmob_drm_crtc* to_shmob_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void shmob_drm_crtc_dpms(struct drm_crtc *crtc, int mode)
{
	struct shmob_drm_crtc *scrtc = to_shmob_crtc(crtc);

	if (scrtc->dpms == mode)
		return;

	if (mode == DRM_MODE_DPMS_ON)
		shmob_drm_crtc_start(scrtc);
	else
		shmob_drm_crtc_stop(scrtc);

	scrtc->dpms = mode;
}