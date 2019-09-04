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
struct qxl_device {int dummy; } ;
struct qxl_crtc {int index; int /*<<< orphan*/  base; } ;
struct drm_plane {int index; int /*<<< orphan*/  base; } ;
struct drm_device {struct qxl_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_PLANE_TYPE_CURSOR ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_PRIMARY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct qxl_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_crtc_init_with_planes (struct drm_device*,int /*<<< orphan*/ *,struct qxl_crtc*,struct qxl_crtc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_plane_cleanup (struct qxl_crtc*) ; 
 int /*<<< orphan*/  kfree (struct qxl_crtc*) ; 
 struct qxl_crtc* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct qxl_crtc* qxl_create_plane (struct qxl_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qxl_crtc_funcs ; 
 int /*<<< orphan*/  qxl_crtc_helper_funcs ; 

__attribute__((used)) static int qdev_crtc_init(struct drm_device *dev, int crtc_id)
{
	struct qxl_crtc *qxl_crtc;
	struct drm_plane *primary, *cursor;
	struct qxl_device *qdev = dev->dev_private;
	int r;

	qxl_crtc = kzalloc(sizeof(struct qxl_crtc), GFP_KERNEL);
	if (!qxl_crtc)
		return -ENOMEM;

	primary = qxl_create_plane(qdev, 1 << crtc_id, DRM_PLANE_TYPE_PRIMARY);
	if (IS_ERR(primary)) {
		r = -ENOMEM;
		goto free_mem;
	}

	cursor = qxl_create_plane(qdev, 1 << crtc_id, DRM_PLANE_TYPE_CURSOR);
	if (IS_ERR(cursor)) {
		r = -ENOMEM;
		goto clean_primary;
	}

	r = drm_crtc_init_with_planes(dev, &qxl_crtc->base, primary, cursor,
				      &qxl_crtc_funcs, NULL);
	if (r)
		goto clean_cursor;

	qxl_crtc->index = crtc_id;
	drm_crtc_helper_add(&qxl_crtc->base, &qxl_crtc_helper_funcs);
	return 0;

clean_cursor:
	drm_plane_cleanup(cursor);
	kfree(cursor);
clean_primary:
	drm_plane_cleanup(primary);
	kfree(primary);
free_mem:
	kfree(qxl_crtc);
	return r;
}