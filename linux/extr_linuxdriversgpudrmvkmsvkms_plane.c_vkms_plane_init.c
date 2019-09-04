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
struct drm_device {int dummy; } ;
struct vkms_device {struct drm_device drm; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_PRIMARY ; 
 int ENOMEM ; 
 struct drm_plane* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_plane*) ; 
 struct drm_plane* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vkms_formats ; 
 int /*<<< orphan*/  vkms_plane_funcs ; 
 int /*<<< orphan*/  vkms_primary_helper_funcs ; 

struct drm_plane *vkms_plane_init(struct vkms_device *vkmsdev)
{
	struct drm_device *dev = &vkmsdev->drm;
	struct drm_plane *plane;
	const u32 *formats;
	int ret, nformats;

	plane = kzalloc(sizeof(*plane), GFP_KERNEL);
	if (!plane)
		return ERR_PTR(-ENOMEM);

	formats = vkms_formats;
	nformats = ARRAY_SIZE(vkms_formats);

	ret = drm_universal_plane_init(dev, plane, 0,
				       &vkms_plane_funcs,
				       formats, nformats,
				       NULL, DRM_PLANE_TYPE_PRIMARY, NULL);
	if (ret) {
		kfree(plane);
		return ERR_PTR(ret);
	}

	drm_plane_helper_add(plane, &vkms_primary_helper_funcs);

	return plane;
}