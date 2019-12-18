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
struct sti_mixer {int /*<<< orphan*/  status; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  STI_MIXER_DISABLING ; 
 int /*<<< orphan*/  drm_crtc_wait_one_vblank (struct drm_crtc*) ; 
 struct sti_mixer* to_sti_mixer (struct drm_crtc*) ; 

__attribute__((used)) static void sti_crtc_atomic_disable(struct drm_crtc *crtc,
				    struct drm_crtc_state *old_state)
{
	struct sti_mixer *mixer = to_sti_mixer(crtc);

	DRM_DEBUG_DRIVER("\n");

	mixer->status = STI_MIXER_DISABLING;

	drm_crtc_wait_one_vblank(crtc);
}