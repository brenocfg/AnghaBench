#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  id_entry; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dev_unref (struct drm_device*) ; 
 int /*<<< orphan*/  mxsfb_driver ; 
 int /*<<< orphan*/  mxsfb_dt_ids ; 
 int mxsfb_load (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxsfb_unload (struct drm_device*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int mxsfb_probe(struct platform_device *pdev)
{
	struct drm_device *drm;
	const struct of_device_id *of_id =
			of_match_device(mxsfb_dt_ids, &pdev->dev);
	int ret;

	if (!pdev->dev.of_node)
		return -ENODEV;

	if (of_id)
		pdev->id_entry = of_id->data;

	drm = drm_dev_alloc(&mxsfb_driver, &pdev->dev);
	if (IS_ERR(drm))
		return PTR_ERR(drm);

	ret = mxsfb_load(drm, 0);
	if (ret)
		goto err_free;

	ret = drm_dev_register(drm, 0);
	if (ret)
		goto err_unload;

	return 0;

err_unload:
	mxsfb_unload(drm);
err_free:
	drm_dev_unref(drm);

	return ret;
}