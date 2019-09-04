#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qxl_fbdev {struct qxl_device* qdev; } ;
struct qxl_device {int dummy; } ;
struct TYPE_2__ {int height; int stride; int /*<<< orphan*/  format; int /*<<< orphan*/  width; } ;
struct qxl_bo {TYPE_1__ surf; } ;
struct drm_mode_fb_cmd2 {int height; int* pitches; int /*<<< orphan*/  width; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  QXL_GEM_DOMAIN_SURFACE ; 
 int /*<<< orphan*/  SPICE_SURFACE_FMT_32_xRGB ; 
 struct qxl_bo* gem_to_qxl_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int qxl_bo_kmap (struct qxl_bo*,int /*<<< orphan*/ *) ; 
 int qxl_bo_pin (struct qxl_bo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qxl_gem_object_create (struct qxl_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,struct drm_gem_object**) ; 
 int /*<<< orphan*/  qxlfb_destroy_pinned_object (struct drm_gem_object*) ; 

__attribute__((used)) static int qxlfb_create_pinned_object(struct qxl_fbdev *qfbdev,
				      const struct drm_mode_fb_cmd2 *mode_cmd,
				      struct drm_gem_object **gobj_p)
{
	struct qxl_device *qdev = qfbdev->qdev;
	struct drm_gem_object *gobj = NULL;
	struct qxl_bo *qbo = NULL;
	int ret;
	int aligned_size, size;
	int height = mode_cmd->height;

	size = mode_cmd->pitches[0] * height;
	aligned_size = ALIGN(size, PAGE_SIZE);
	/* TODO: unallocate and reallocate surface0 for real. Hack to just
	 * have a large enough surface0 for 1024x768 Xorg 32bpp mode */
	ret = qxl_gem_object_create(qdev, aligned_size, 0,
				    QXL_GEM_DOMAIN_SURFACE,
				    false, /* is discardable */
				    false, /* is kernel (false means device) */
				    NULL,
				    &gobj);
	if (ret) {
		pr_err("failed to allocate framebuffer (%d)\n",
		       aligned_size);
		return -ENOMEM;
	}
	qbo = gem_to_qxl_bo(gobj);

	qbo->surf.width = mode_cmd->width;
	qbo->surf.height = mode_cmd->height;
	qbo->surf.stride = mode_cmd->pitches[0];
	qbo->surf.format = SPICE_SURFACE_FMT_32_xRGB;

	ret = qxl_bo_pin(qbo, QXL_GEM_DOMAIN_SURFACE, NULL);
	if (ret) {
		goto out_unref;
	}
	ret = qxl_bo_kmap(qbo, NULL);

	if (ret)
		goto out_unref;

	*gobj_p = gobj;
	return 0;
out_unref:
	qxlfb_destroy_pinned_object(gobj);
	*gobj_p = NULL;
	return ret;
}