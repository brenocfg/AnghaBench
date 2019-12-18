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
struct rcar_du_device {int dummy; } ;
struct drm_device {struct rcar_du_device* dev_private; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCAR_DU_FEATURE_VSP1_SOURCE ; 
 int drm_atomic_helper_check (struct drm_device*,struct drm_atomic_state*) ; 
 int rcar_du_atomic_check_planes (struct drm_device*,struct drm_atomic_state*) ; 
 scalar_t__ rcar_du_has (struct rcar_du_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_du_atomic_check(struct drm_device *dev,
				struct drm_atomic_state *state)
{
	struct rcar_du_device *rcdu = dev->dev_private;
	int ret;

	ret = drm_atomic_helper_check(dev, state);
	if (ret)
		return ret;

	if (rcar_du_has(rcdu, RCAR_DU_FEATURE_VSP1_SOURCE))
		return 0;

	return rcar_du_atomic_check_planes(dev, state);
}