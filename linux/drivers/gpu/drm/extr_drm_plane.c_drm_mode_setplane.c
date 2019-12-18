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
struct drm_plane {int dummy; } ;
struct drm_mode_set_plane {int /*<<< orphan*/  src_h; int /*<<< orphan*/  src_w; int /*<<< orphan*/  src_y; int /*<<< orphan*/  src_x; int /*<<< orphan*/  crtc_h; int /*<<< orphan*/  crtc_w; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; scalar_t__ crtc_id; scalar_t__ fb_id; scalar_t__ plane_id; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,scalar_t__) ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct drm_crtc* drm_crtc_find (struct drm_device*,struct drm_file*,scalar_t__) ; 
 struct drm_framebuffer* drm_framebuffer_lookup (struct drm_device*,struct drm_file*,scalar_t__) ; 
 int /*<<< orphan*/  drm_framebuffer_put (struct drm_framebuffer*) ; 
 struct drm_plane* drm_plane_find (struct drm_device*,struct drm_file*,scalar_t__) ; 
 int setplane_internal (struct drm_plane*,struct drm_crtc*,struct drm_framebuffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int drm_mode_setplane(struct drm_device *dev, void *data,
		      struct drm_file *file_priv)
{
	struct drm_mode_set_plane *plane_req = data;
	struct drm_plane *plane;
	struct drm_crtc *crtc = NULL;
	struct drm_framebuffer *fb = NULL;
	int ret;

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return -EOPNOTSUPP;

	/*
	 * First, find the plane, crtc, and fb objects.  If not available,
	 * we don't bother to call the driver.
	 */
	plane = drm_plane_find(dev, file_priv, plane_req->plane_id);
	if (!plane) {
		DRM_DEBUG_KMS("Unknown plane ID %d\n",
			      plane_req->plane_id);
		return -ENOENT;
	}

	if (plane_req->fb_id) {
		fb = drm_framebuffer_lookup(dev, file_priv, plane_req->fb_id);
		if (!fb) {
			DRM_DEBUG_KMS("Unknown framebuffer ID %d\n",
				      plane_req->fb_id);
			return -ENOENT;
		}

		crtc = drm_crtc_find(dev, file_priv, plane_req->crtc_id);
		if (!crtc) {
			drm_framebuffer_put(fb);
			DRM_DEBUG_KMS("Unknown crtc ID %d\n",
				      plane_req->crtc_id);
			return -ENOENT;
		}
	}

	ret = setplane_internal(plane, crtc, fb,
				plane_req->crtc_x, plane_req->crtc_y,
				plane_req->crtc_w, plane_req->crtc_h,
				plane_req->src_x, plane_req->src_y,
				plane_req->src_w, plane_req->src_h);

	if (fb)
		drm_framebuffer_put(fb);

	return ret;
}