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
struct omap_drm_private {unsigned int num_pipes; TYPE_1__* pipes; } ;
struct drm_device {struct omap_drm_private* dev_private; } ;
struct TYPE_2__ {scalar_t__ connector; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_connector_disable_hpd (scalar_t__) ; 

__attribute__((used)) static void omap_modeset_disable_external_hpd(struct drm_device *ddev)
{
	struct omap_drm_private *priv = ddev->dev_private;
	unsigned int i;

	for (i = 0; i < priv->num_pipes; i++) {
		if (priv->pipes[i].connector)
			omap_connector_disable_hpd(priv->pipes[i].connector);
	}
}