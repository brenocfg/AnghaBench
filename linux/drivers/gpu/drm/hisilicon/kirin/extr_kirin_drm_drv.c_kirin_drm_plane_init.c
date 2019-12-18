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
struct kirin_drm_data {int /*<<< orphan*/  plane_helper_funcs; int /*<<< orphan*/  channel_formats_cnt; int /*<<< orphan*/  channel_formats; int /*<<< orphan*/  plane_funcs; } ;
struct drm_plane {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ ) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kirin_drm_plane_init(struct drm_device *dev, struct drm_plane *plane,
				enum drm_plane_type type,
				const struct kirin_drm_data *data)
{
	int ret = 0;

	ret = drm_universal_plane_init(dev, plane, 1, data->plane_funcs,
				       data->channel_formats,
				       data->channel_formats_cnt,
				       NULL, type, NULL);
	if (ret) {
		DRM_ERROR("fail to init plane, ch=%d\n", 0);
		return ret;
	}

	drm_plane_helper_add(plane, data->plane_helper_funcs);

	return 0;
}