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
 int /*<<< orphan*/  const* icl_hdr_plane_formats ; 
 scalar_t__ icl_is_hdr_plane (struct drm_i915_private*,int) ; 
 scalar_t__ icl_is_nv12_y_plane (int) ; 
 int /*<<< orphan*/  const* icl_sdr_uv_plane_formats ; 
 int /*<<< orphan*/  const* icl_sdr_y_plane_formats ; 

__attribute__((used)) static const u32 *icl_get_plane_formats(struct drm_i915_private *dev_priv,
					enum pipe pipe, enum plane_id plane_id,
					int *num_formats)
{
	if (icl_is_hdr_plane(dev_priv, plane_id)) {
		*num_formats = ARRAY_SIZE(icl_hdr_plane_formats);
		return icl_hdr_plane_formats;
	} else if (icl_is_nv12_y_plane(plane_id)) {
		*num_formats = ARRAY_SIZE(icl_sdr_y_plane_formats);
		return icl_sdr_y_plane_formats;
	} else {
		*num_formats = ARRAY_SIZE(icl_sdr_uv_plane_formats);
		return icl_sdr_uv_plane_formats;
	}
}