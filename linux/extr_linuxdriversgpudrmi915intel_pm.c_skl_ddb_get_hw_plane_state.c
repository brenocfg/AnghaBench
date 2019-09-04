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
typedef  int u32 ;
struct skl_ddb_allocation {int /*<<< orphan*/ ** plane; int /*<<< orphan*/ ** uv_plane; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  CUR_BUF_CFG (int const) ; 
 int DRM_FORMAT_NV12 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLANE_BUF_CFG (int const,int const) ; 
 int /*<<< orphan*/  PLANE_CTL (int const,int const) ; 
 int PLANE_CTL_ALPHA_MASK ; 
 int PLANE_CTL_ENABLE ; 
 int PLANE_CTL_FORMAT_MASK ; 
 int PLANE_CTL_ORDER_RGBX ; 
 int const PLANE_CURSOR ; 
 int /*<<< orphan*/  PLANE_NV12_BUF_CFG (int const,int const) ; 
 int /*<<< orphan*/  skl_ddb_entry_init_from_hw (struct drm_i915_private*,int /*<<< orphan*/ *,int) ; 
 int skl_format_to_fourcc (int,int,int) ; 

__attribute__((used)) static void
skl_ddb_get_hw_plane_state(struct drm_i915_private *dev_priv,
			   const enum pipe pipe,
			   const enum plane_id plane_id,
			   struct skl_ddb_allocation *ddb /* out */)
{
	u32 val, val2 = 0;
	int fourcc, pixel_format;

	/* Cursor doesn't support NV12/planar, so no extra calculation needed */
	if (plane_id == PLANE_CURSOR) {
		val = I915_READ(CUR_BUF_CFG(pipe));
		skl_ddb_entry_init_from_hw(dev_priv,
					   &ddb->plane[pipe][plane_id], val);
		return;
	}

	val = I915_READ(PLANE_CTL(pipe, plane_id));

	/* No DDB allocated for disabled planes */
	if (!(val & PLANE_CTL_ENABLE))
		return;

	pixel_format = val & PLANE_CTL_FORMAT_MASK;
	fourcc = skl_format_to_fourcc(pixel_format,
				      val & PLANE_CTL_ORDER_RGBX,
				      val & PLANE_CTL_ALPHA_MASK);

	val = I915_READ(PLANE_BUF_CFG(pipe, plane_id));
	val2 = I915_READ(PLANE_NV12_BUF_CFG(pipe, plane_id));

	if (fourcc == DRM_FORMAT_NV12) {
		skl_ddb_entry_init_from_hw(dev_priv,
					   &ddb->plane[pipe][plane_id], val2);
		skl_ddb_entry_init_from_hw(dev_priv,
					   &ddb->uv_plane[pipe][plane_id], val);
	} else {
		skl_ddb_entry_init_from_hw(dev_priv,
					   &ddb->plane[pipe][plane_id], val);
	}
}