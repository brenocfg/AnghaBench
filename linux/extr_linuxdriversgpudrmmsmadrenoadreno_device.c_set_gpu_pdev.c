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
struct platform_device {int dummy; } ;
struct msm_drm_private {struct platform_device* gpu_pdev; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;

/* Variables and functions */

__attribute__((used)) static void set_gpu_pdev(struct drm_device *dev,
		struct platform_device *pdev)
{
	struct msm_drm_private *priv = dev->dev_private;
	priv->gpu_pdev = pdev;
}