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
struct vkms_output {int /*<<< orphan*/  vblank_hrtimer; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 struct vkms_output* drm_crtc_to_vkms_output (struct drm_crtc*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vkms_disable_vblank(struct drm_crtc *crtc)
{
	struct vkms_output *out = drm_crtc_to_vkms_output(crtc);

	hrtimer_cancel(&out->vblank_hrtimer);
}