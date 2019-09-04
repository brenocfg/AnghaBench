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
struct ade_plane {int /*<<< orphan*/  base; int /*<<< orphan*/  ch; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ade_get_channel_formats (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  ade_plane_funcs ; 
 int /*<<< orphan*/  ade_plane_helper_funcs ; 
 int /*<<< orphan*/  drm_plane_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ade_plane_init(struct drm_device *dev, struct ade_plane *aplane,
			  enum drm_plane_type type)
{
	const u32 *fmts;
	u32 fmts_cnt;
	int ret = 0;

	/* get  properties */
	fmts_cnt = ade_get_channel_formats(aplane->ch, &fmts);
	if (ret)
		return ret;

	ret = drm_universal_plane_init(dev, &aplane->base, 1, &ade_plane_funcs,
				       fmts, fmts_cnt, NULL, type, NULL);
	if (ret) {
		DRM_ERROR("fail to init plane, ch=%d\n", aplane->ch);
		return ret;
	}

	drm_plane_helper_add(&aplane->base, &ade_plane_helper_funcs);

	return 0;
}