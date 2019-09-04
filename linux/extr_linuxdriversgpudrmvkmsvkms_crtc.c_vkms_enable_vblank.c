#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * function; } ;
struct vkms_output {int /*<<< orphan*/  period_ns; TYPE_1__ vblank_hrtimer; } ;
struct drm_vblank_crtc {int /*<<< orphan*/  framedur_ns; } ;
struct drm_device {struct drm_vblank_crtc* vblank; } ;
struct drm_crtc {int /*<<< orphan*/  mode; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  drm_calc_timestamping_constants (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 unsigned int drm_crtc_index (struct drm_crtc*) ; 
 struct vkms_output* drm_crtc_to_vkms_output (struct drm_crtc*) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkms_vblank_simulate ; 

__attribute__((used)) static int vkms_enable_vblank(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	unsigned int pipe = drm_crtc_index(crtc);
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];
	struct vkms_output *out = drm_crtc_to_vkms_output(crtc);

	drm_calc_timestamping_constants(crtc, &crtc->mode);

	hrtimer_init(&out->vblank_hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	out->vblank_hrtimer.function = &vkms_vblank_simulate;
	out->period_ns = ktime_set(0, vblank->framedur_ns);
	hrtimer_start(&out->vblank_hrtimer, out->period_ns, HRTIMER_MODE_REL);

	return 0;
}