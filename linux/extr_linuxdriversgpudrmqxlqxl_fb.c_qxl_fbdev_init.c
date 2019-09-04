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

/* Variables and functions */

int qxl_fbdev_init(struct qxl_device *qdev)
{
	int ret = 0;

#ifdef CONFIG_DRM_FBDEV_EMULATION
	struct qxl_fbdev *qfbdev;
	int bpp_sel = 32; /* TODO: parameter from somewhere? */

	qfbdev = kzalloc(sizeof(struct qxl_fbdev), GFP_KERNEL);
	if (!qfbdev)
		return -ENOMEM;

	qfbdev->qdev = qdev;
	qdev->mode_info.qfbdev = qfbdev;
	spin_lock_init(&qfbdev->delayed_ops_lock);
	INIT_LIST_HEAD(&qfbdev->delayed_ops);

	drm_fb_helper_prepare(&qdev->ddev, &qfbdev->helper,
			      &qxl_fb_helper_funcs);

	ret = drm_fb_helper_init(&qdev->ddev, &qfbdev->helper,
				 QXLFB_CONN_LIMIT);
	if (ret)
		goto free;

	ret = drm_fb_helper_single_add_all_connectors(&qfbdev->helper);
	if (ret)
		goto fini;

	ret = drm_fb_helper_initial_config(&qfbdev->helper, bpp_sel);
	if (ret)
		goto fini;

	return 0;

fini:
	drm_fb_helper_fini(&qfbdev->helper);
free:
	kfree(qfbdev);
#endif

	return ret;
}