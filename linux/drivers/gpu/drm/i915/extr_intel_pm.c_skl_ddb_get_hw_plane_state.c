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
struct skl_ddb_entry {int dummy; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  CUR_BUF_CFG (int const) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PLANE_BUF_CFG (int const,int const) ; 
 int /*<<< orphan*/  PLANE_CTL (int const,int const) ; 
 int PLANE_CTL_ALPHA_MASK ; 
 int PLANE_CTL_ENABLE ; 
 int PLANE_CTL_FORMAT_MASK ; 
 int PLANE_CTL_ORDER_RGBX ; 
 int const PLANE_CURSOR ; 
 int /*<<< orphan*/  PLANE_NV12_BUF_CFG (int const,int const) ; 
 scalar_t__ is_planar_yuv_format (int) ; 
 int /*<<< orphan*/  skl_ddb_entry_init_from_hw (struct drm_i915_private*,struct skl_ddb_entry*,int) ; 
 int skl_format_to_fourcc (int,int,int) ; 
 int /*<<< orphan*/  swap (int,int) ; 

__attribute__((used)) static void
skl_ddb_get_hw_plane_state(struct drm_i915_private *dev_priv,
			   const enum pipe pipe,
			   const enum plane_id plane_id,
			   struct skl_ddb_entry *ddb_y,
			   struct skl_ddb_entry *ddb_uv)
{
	u32 val, val2;
	u32 fourcc = 0;

	/* Cursor doesn't support NV12/planar, so no extra calculation needed */
	if (plane_id == PLANE_CURSOR) {
		val = I915_READ(CUR_BUF_CFG(pipe));
		skl_ddb_entry_init_from_hw(dev_priv, ddb_y, val);
		return;
	}

	val = I915_READ(PLANE_CTL(pipe, plane_id));

	/* No DDB allocated for disabled planes */
	if (val & PLANE_CTL_ENABLE)
		fourcc = skl_format_to_fourcc(val & PLANE_CTL_FORMAT_MASK,
					      val & PLANE_CTL_ORDER_RGBX,
					      val & PLANE_CTL_ALPHA_MASK);

	if (INTEL_GEN(dev_priv) >= 11) {
		val = I915_READ(PLANE_BUF_CFG(pipe, plane_id));
		skl_ddb_entry_init_from_hw(dev_priv, ddb_y, val);
	} else {
		val = I915_READ(PLANE_BUF_CFG(pipe, plane_id));
		val2 = I915_READ(PLANE_NV12_BUF_CFG(pipe, plane_id));

		if (is_planar_yuv_format(fourcc))
			swap(val, val2);

		skl_ddb_entry_init_from_hw(dev_priv, ddb_y, val);
		skl_ddb_entry_init_from_hw(dev_priv, ddb_uv, val2);
	}
}