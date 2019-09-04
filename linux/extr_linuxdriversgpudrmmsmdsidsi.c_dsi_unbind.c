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
struct msm_dsi {int id; } ;
struct msm_drm_private {int /*<<< orphan*/ ** dsi; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 void* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dsi_destroy (struct msm_dsi*) ; 

__attribute__((used)) static void dsi_unbind(struct device *dev, struct device *master,
		void *data)
{
	struct drm_device *drm = dev_get_drvdata(master);
	struct msm_drm_private *priv = drm->dev_private;
	struct msm_dsi *msm_dsi = dev_get_drvdata(dev);
	int id = msm_dsi->id;

	if (priv->dsi[id]) {
		dsi_destroy(msm_dsi);
		priv->dsi[id] = NULL;
	}
}