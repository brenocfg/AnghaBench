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
struct msm_drm_private {TYPE_1__* hdmi; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ audio_pdev; } ;

/* Variables and functions */
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  msm_hdmi_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 

__attribute__((used)) static void msm_hdmi_unbind(struct device *dev, struct device *master,
		void *data)
{
	struct drm_device *drm = dev_get_drvdata(master);
	struct msm_drm_private *priv = drm->dev_private;
	if (priv->hdmi) {
		if (priv->hdmi->audio_pdev)
			platform_device_unregister(priv->hdmi->audio_pdev);

		msm_hdmi_destroy(priv->hdmi);
		priv->hdmi = NULL;
	}
}