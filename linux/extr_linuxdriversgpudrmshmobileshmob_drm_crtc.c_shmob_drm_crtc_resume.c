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
struct shmob_drm_crtc {scalar_t__ dpms; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  shmob_drm_crtc_start (struct shmob_drm_crtc*) ; 

void shmob_drm_crtc_resume(struct shmob_drm_crtc *scrtc)
{
	if (scrtc->dpms != DRM_MODE_DPMS_ON)
		return;

	shmob_drm_crtc_start(scrtc);
}