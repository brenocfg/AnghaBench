#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct idr {int dummy; } ;
struct drm_mode_object {scalar_t__ type; int id; } ;
struct drm_file {int /*<<< orphan*/  universal_planes; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {TYPE_4__* cursor; TYPE_2__* primary; } ;
struct TYPE_7__ {int id; } ;
struct TYPE_8__ {TYPE_3__ base; } ;
struct TYPE_5__ {int id; } ;
struct TYPE_6__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_DEBUG_LEASE (char*,...) ; 
 int /*<<< orphan*/  DRM_MODE_OBJECT_ANY ; 
 scalar_t__ DRM_MODE_OBJECT_CRTC ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_lease_idr_object ; 
 struct drm_mode_object* drm_mode_object_find (struct drm_device*,struct drm_file*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_object_lease_required (scalar_t__) ; 
 int /*<<< orphan*/  drm_mode_object_put (struct drm_mode_object*) ; 
 int idr_alloc (struct idr*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct drm_mode_object** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_mode_object**) ; 
 struct drm_crtc* obj_to_crtc (struct drm_mode_object*) ; 
 int validate_lease (struct drm_device*,int,struct drm_mode_object**,int) ; 

__attribute__((used)) static int fill_object_idr(struct drm_device *dev,
			   struct drm_file *lessor_priv,
			   struct idr *leases,
			   int object_count,
			   u32 *object_ids)
{
	struct drm_mode_object **objects;
	u32 o;
	int ret;
	bool universal_planes = READ_ONCE(lessor_priv->universal_planes);

	objects = kcalloc(object_count, sizeof(struct drm_mode_object *),
			  GFP_KERNEL);
	if (!objects)
		return -ENOMEM;

	/* step one - get references to all the mode objects
	   and check for validity. */
	for (o = 0; o < object_count; o++) {
		objects[o] = drm_mode_object_find(dev, lessor_priv,
						  object_ids[o],
						  DRM_MODE_OBJECT_ANY);
		if (!objects[o]) {
			ret = -ENOENT;
			goto out_free_objects;
		}

		if (!drm_mode_object_lease_required(objects[o]->type)) {
			DRM_DEBUG_KMS("invalid object for lease\n");
			ret = -EINVAL;
			goto out_free_objects;
		}
	}

	ret = validate_lease(dev, object_count, objects, universal_planes);
	if (ret) {
		DRM_DEBUG_LEASE("lease validation failed\n");
		goto out_free_objects;
	}

	/* add their IDs to the lease request - taking into account
	   universal planes */
	for (o = 0; o < object_count; o++) {
		struct drm_mode_object *obj = objects[o];
		u32 object_id = objects[o]->id;
		DRM_DEBUG_LEASE("Adding object %d to lease\n", object_id);

		/*
		 * We're using an IDR to hold the set of leased
		 * objects, but we don't need to point at the object's
		 * data structure from the lease as the main object_idr
		 * will be used to actually find that. Instead, all we
		 * really want is a 'leased/not-leased' result, for
		 * which any non-NULL pointer will work fine.
		 */
		ret = idr_alloc(leases, &drm_lease_idr_object , object_id, object_id + 1, GFP_KERNEL);
		if (ret < 0) {
			DRM_DEBUG_LEASE("Object %d cannot be inserted into leases (%d)\n",
					object_id, ret);
			goto out_free_objects;
		}
		if (obj->type == DRM_MODE_OBJECT_CRTC && !universal_planes) {
			struct drm_crtc *crtc = obj_to_crtc(obj);
			ret = idr_alloc(leases, &drm_lease_idr_object, crtc->primary->base.id, crtc->primary->base.id + 1, GFP_KERNEL);
			if (ret < 0) {
				DRM_DEBUG_LEASE("Object primary plane %d cannot be inserted into leases (%d)\n",
						object_id, ret);
				goto out_free_objects;
			}
			if (crtc->cursor) {
				ret = idr_alloc(leases, &drm_lease_idr_object, crtc->cursor->base.id, crtc->cursor->base.id + 1, GFP_KERNEL);
				if (ret < 0) {
					DRM_DEBUG_LEASE("Object cursor plane %d cannot be inserted into leases (%d)\n",
							object_id, ret);
					goto out_free_objects;
				}
			}
		}
	}

	ret = 0;
out_free_objects:
	for (o = 0; o < object_count; o++) {
		if (objects[o])
			drm_mode_object_put(objects[o]);
	}
	kfree(objects);
	return ret;
}