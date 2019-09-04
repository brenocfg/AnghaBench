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
struct skl_plane_wm {scalar_t__ is_planar; int /*<<< orphan*/  trans_wm; int /*<<< orphan*/ * wm; } ;
struct skl_ddb_allocation {int /*<<< orphan*/ ** plane; int /*<<< orphan*/ ** uv_plane; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct intel_crtc {int pipe; struct drm_crtc base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PLANE_BUF_CFG (int,int) ; 
 int /*<<< orphan*/  PLANE_NV12_BUF_CFG (int,int) ; 
 int /*<<< orphan*/  PLANE_WM (int,int,int) ; 
 int /*<<< orphan*/  PLANE_WM_TRANS (int,int) ; 
 int ilk_wm_max_level (struct drm_i915_private*) ; 
 void skl_ddb_entry_write (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skl_write_wm_level (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void skl_write_plane_wm(struct intel_crtc *intel_crtc,
			       const struct skl_plane_wm *wm,
			       const struct skl_ddb_allocation *ddb,
			       enum plane_id plane_id)
{
	struct drm_crtc *crtc = &intel_crtc->base;
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	int level, max_level = ilk_wm_max_level(dev_priv);
	enum pipe pipe = intel_crtc->pipe;

	for (level = 0; level <= max_level; level++) {
		skl_write_wm_level(dev_priv, PLANE_WM(pipe, plane_id, level),
				   &wm->wm[level]);
	}
	skl_write_wm_level(dev_priv, PLANE_WM_TRANS(pipe, plane_id),
			   &wm->trans_wm);

	skl_ddb_entry_write(dev_priv, PLANE_BUF_CFG(pipe, plane_id),
			    &ddb->plane[pipe][plane_id]);
	if (INTEL_GEN(dev_priv) >= 11)
		return skl_ddb_entry_write(dev_priv,
					   PLANE_BUF_CFG(pipe, plane_id),
					   &ddb->plane[pipe][plane_id]);
	if (wm->is_planar) {
		skl_ddb_entry_write(dev_priv, PLANE_BUF_CFG(pipe, plane_id),
				    &ddb->uv_plane[pipe][plane_id]);
		skl_ddb_entry_write(dev_priv,
				    PLANE_NV12_BUF_CFG(pipe, plane_id),
				    &ddb->plane[pipe][plane_id]);
	} else {
		skl_ddb_entry_write(dev_priv, PLANE_BUF_CFG(pipe, plane_id),
				    &ddb->plane[pipe][plane_id]);
		I915_WRITE(PLANE_NV12_BUF_CFG(pipe, plane_id), 0x0);
	}
}