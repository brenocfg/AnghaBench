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
 int /*<<< orphan*/  HAS_FBC (struct drm_i915_private*) ; 
 int PIPE_A ; 
 int PLANE_PRIMARY ; 

__attribute__((used)) static bool skl_plane_has_fbc(struct drm_i915_private *dev_priv,
			      enum pipe pipe, enum plane_id plane_id)
{
	if (!HAS_FBC(dev_priv))
		return false;

	return pipe == PIPE_A && plane_id == PLANE_PRIMARY;
}