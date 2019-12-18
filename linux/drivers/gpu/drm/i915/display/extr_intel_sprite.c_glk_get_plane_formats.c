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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* glk_planar_formats ; 
 int /*<<< orphan*/  const* skl_plane_formats ; 
 scalar_t__ skl_plane_has_planar (struct drm_i915_private*,int,int) ; 

__attribute__((used)) static const u32 *glk_get_plane_formats(struct drm_i915_private *dev_priv,
					enum pipe pipe, enum plane_id plane_id,
					int *num_formats)
{
	if (skl_plane_has_planar(dev_priv, pipe, plane_id)) {
		*num_formats = ARRAY_SIZE(glk_planar_formats);
		return glk_planar_formats;
	} else {
		*num_formats = ARRAY_SIZE(skl_plane_formats);
		return skl_plane_formats;
	}
}