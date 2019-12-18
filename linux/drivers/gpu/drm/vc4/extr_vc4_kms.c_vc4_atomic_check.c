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
struct drm_device {int dummy; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int drm_atomic_helper_check (struct drm_device*,struct drm_atomic_state*) ; 
 int vc4_ctm_atomic_check (struct drm_device*,struct drm_atomic_state*) ; 
 int vc4_load_tracker_atomic_check (struct drm_atomic_state*) ; 

__attribute__((used)) static int
vc4_atomic_check(struct drm_device *dev, struct drm_atomic_state *state)
{
	int ret;

	ret = vc4_ctm_atomic_check(dev, state);
	if (ret < 0)
		return ret;

	ret = drm_atomic_helper_check(dev, state);
	if (ret)
		return ret;

	return vc4_load_tracker_atomic_check(state);
}