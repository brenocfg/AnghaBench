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
struct venc_device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct venc_device*) ; 
 struct venc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  venc_component_ops ; 
 int /*<<< orphan*/  venc_uninit_output (struct venc_device*) ; 

__attribute__((used)) static int venc_remove(struct platform_device *pdev)
{
	struct venc_device *venc = platform_get_drvdata(pdev);

	component_del(&pdev->dev, &venc_component_ops);

	venc_uninit_output(venc);

	pm_runtime_disable(&pdev->dev);

	kfree(venc);
	return 0;
}