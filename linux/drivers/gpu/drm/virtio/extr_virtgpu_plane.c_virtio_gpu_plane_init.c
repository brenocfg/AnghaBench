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
typedef  int /*<<< orphan*/  uint32_t ;
struct virtio_gpu_device {struct drm_device* ddev; } ;
struct drm_plane_helper_funcs {int dummy; } ;
struct drm_plane {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int DRM_PLANE_TYPE_CURSOR ; 
 int ENOMEM ; 
 struct drm_plane* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,struct drm_plane_helper_funcs const*) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_plane*) ; 
 struct drm_plane* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * virtio_gpu_cursor_formats ; 
 struct drm_plane_helper_funcs virtio_gpu_cursor_helper_funcs ; 
 int /*<<< orphan*/ * virtio_gpu_formats ; 
 int /*<<< orphan*/  virtio_gpu_plane_funcs ; 
 struct drm_plane_helper_funcs virtio_gpu_primary_helper_funcs ; 

struct drm_plane *virtio_gpu_plane_init(struct virtio_gpu_device *vgdev,
					enum drm_plane_type type,
					int index)
{
	struct drm_device *dev = vgdev->ddev;
	const struct drm_plane_helper_funcs *funcs;
	struct drm_plane *plane;
	const uint32_t *formats;
	int ret, nformats;

	plane = kzalloc(sizeof(*plane), GFP_KERNEL);
	if (!plane)
		return ERR_PTR(-ENOMEM);

	if (type == DRM_PLANE_TYPE_CURSOR) {
		formats = virtio_gpu_cursor_formats;
		nformats = ARRAY_SIZE(virtio_gpu_cursor_formats);
		funcs = &virtio_gpu_cursor_helper_funcs;
	} else {
		formats = virtio_gpu_formats;
		nformats = ARRAY_SIZE(virtio_gpu_formats);
		funcs = &virtio_gpu_primary_helper_funcs;
	}
	ret = drm_universal_plane_init(dev, plane, 1 << index,
				       &virtio_gpu_plane_funcs,
				       formats, nformats,
				       NULL, type, NULL);
	if (ret)
		goto err_plane_init;

	drm_plane_helper_add(plane, funcs);
	return plane;

err_plane_init:
	kfree(plane);
	return ERR_PTR(ret);
}