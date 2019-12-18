#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct drm_file {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_4__ {int size; } ;
struct armada_gem_object {int /*<<< orphan*/ * update; struct armada_crtc* update_data; TYPE_2__ obj; int /*<<< orphan*/  addr; } ;
struct armada_crtc {int cursor_w; int cursor_h; struct armada_gem_object* cursor_obj; TYPE_1__* variant; } ;
struct TYPE_3__ {int /*<<< orphan*/  has_spu_adv_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int armada_drm_crtc_cursor_update (struct armada_crtc*,int) ; 
 struct armada_gem_object* armada_gem_object_lookup (struct drm_file*,int) ; 
 int /*<<< orphan*/ * cursor_update ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (TYPE_2__*) ; 
 struct armada_crtc* drm_to_armada_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int armada_drm_crtc_cursor_set(struct drm_crtc *crtc,
	struct drm_file *file, uint32_t handle, uint32_t w, uint32_t h)
{
	struct armada_crtc *dcrtc = drm_to_armada_crtc(crtc);
	struct armada_gem_object *obj = NULL;
	int ret;

	/* If no cursor support, replicate drm's return value */
	if (!dcrtc->variant->has_spu_adv_reg)
		return -ENXIO;

	if (handle && w > 0 && h > 0) {
		/* maximum size is 64x32 or 32x64 */
		if (w > 64 || h > 64 || (w > 32 && h > 32))
			return -ENOMEM;

		obj = armada_gem_object_lookup(file, handle);
		if (!obj)
			return -ENOENT;

		/* Must be a kernel-mapped object */
		if (!obj->addr) {
			drm_gem_object_put_unlocked(&obj->obj);
			return -EINVAL;
		}

		if (obj->obj.size < w * h * 4) {
			DRM_ERROR("buffer is too small\n");
			drm_gem_object_put_unlocked(&obj->obj);
			return -ENOMEM;
		}
	}

	if (dcrtc->cursor_obj) {
		dcrtc->cursor_obj->update = NULL;
		dcrtc->cursor_obj->update_data = NULL;
		drm_gem_object_put_unlocked(&dcrtc->cursor_obj->obj);
	}
	dcrtc->cursor_obj = obj;
	dcrtc->cursor_w = w;
	dcrtc->cursor_h = h;
	ret = armada_drm_crtc_cursor_update(dcrtc, true);
	if (obj) {
		obj->update_data = dcrtc;
		obj->update = cursor_update;
	}

	return ret;
}