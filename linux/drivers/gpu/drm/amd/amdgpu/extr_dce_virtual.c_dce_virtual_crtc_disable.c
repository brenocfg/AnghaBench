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
struct amdgpu_crtc {int /*<<< orphan*/ * connector; int /*<<< orphan*/ * encoder; int /*<<< orphan*/  pll_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_PPLL_INVALID ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  dce_virtual_crtc_dpms (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void dce_virtual_crtc_disable(struct drm_crtc *crtc)
{
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(crtc);

	dce_virtual_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);

	amdgpu_crtc->pll_id = ATOM_PPLL_INVALID;
	amdgpu_crtc->encoder = NULL;
	amdgpu_crtc->connector = NULL;
}