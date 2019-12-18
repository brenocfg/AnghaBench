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

/* Variables and functions */
 int BIT (int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int icl_hdr_plane_mask () ; 

bool icl_is_hdr_plane(struct drm_i915_private *dev_priv, enum plane_id plane_id)
{
	return INTEL_GEN(dev_priv) >= 11 &&
		icl_hdr_plane_mask() & BIT(plane_id);
}