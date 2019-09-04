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
struct tilcdc_drm_private {int /*<<< orphan*/ * connector_funcs; int /*<<< orphan*/  external_connector; } ;
struct drm_device {struct tilcdc_drm_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_helper_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void tilcdc_remove_external_device(struct drm_device *dev)
{
	struct tilcdc_drm_private *priv = dev->dev_private;

	/* Restore the original helper functions, if any. */
	if (IS_ERR(priv->connector_funcs))
		drm_connector_helper_add(priv->external_connector, NULL);
	else if (priv->connector_funcs)
		drm_connector_helper_add(priv->external_connector,
					 priv->connector_funcs);
}