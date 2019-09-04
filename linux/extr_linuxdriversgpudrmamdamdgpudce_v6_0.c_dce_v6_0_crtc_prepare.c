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
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_lock (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_crtc_powergate (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dce_v6_0_crtc_dpms (struct drm_crtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce_v6_0_crtc_prepare(struct drm_crtc *crtc)
{
	/* disable crtc pair power gating before programming */
	amdgpu_atombios_crtc_powergate(crtc, ATOM_DISABLE);
	amdgpu_atombios_crtc_lock(crtc, ATOM_ENABLE);
	dce_v6_0_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);
}