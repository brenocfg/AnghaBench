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
struct vidi_context {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int component_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_connection ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vidi_context* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct vidi_context*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vidi_component_ops ; 
 int /*<<< orphan*/  vidi_fake_vblank_timer ; 

__attribute__((used)) static int vidi_probe(struct platform_device *pdev)
{
	struct vidi_context *ctx;
	int ret;

	ctx = devm_kzalloc(&pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->pdev = pdev;

	timer_setup(&ctx->timer, vidi_fake_vblank_timer, 0);

	mutex_init(&ctx->lock);

	platform_set_drvdata(pdev, ctx);

	ret = device_create_file(&pdev->dev, &dev_attr_connection);
	if (ret < 0) {
		DRM_ERROR("failed to create connection sysfs.\n");
		return ret;
	}

	ret = component_add(&pdev->dev, &vidi_component_ops);
	if (ret)
		goto err_remove_file;

	return ret;

err_remove_file:
	device_remove_file(&pdev->dev, &dev_attr_connection);

	return ret;
}