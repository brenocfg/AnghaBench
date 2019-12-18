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
struct drm_i915_private {int dummy; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 int PIPE_C ; 
 int PLANE_PRIMARY ; 
 int PLANE_SPRITE0 ; 

__attribute__((used)) static bool skl_plane_has_planar(struct drm_i915_private *dev_priv,
				 enum pipe pipe, enum plane_id plane_id)
{
	/* Display WA #0870: skl, bxt */
	if (IS_SKYLAKE(dev_priv) || IS_BROXTON(dev_priv))
		return false;

	if (IS_GEN(dev_priv, 9) && !IS_GEMINILAKE(dev_priv) && pipe == PIPE_C)
		return false;

	if (plane_id != PLANE_PRIMARY && plane_id != PLANE_SPRITE0)
		return false;

	return true;
}