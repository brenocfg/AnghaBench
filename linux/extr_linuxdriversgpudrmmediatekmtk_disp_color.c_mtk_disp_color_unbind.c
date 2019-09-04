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
struct mtk_disp_color {int /*<<< orphan*/  ddp_comp; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mtk_disp_color* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mtk_ddp_comp_unregister (struct drm_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_disp_color_unbind(struct device *dev, struct device *master,
				  void *data)
{
	struct mtk_disp_color *priv = dev_get_drvdata(dev);
	struct drm_device *drm_dev = data;

	mtk_ddp_comp_unregister(drm_dev, &priv->ddp_comp);
}