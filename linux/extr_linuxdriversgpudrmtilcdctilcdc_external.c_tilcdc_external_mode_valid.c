#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tilcdc_drm_private {TYPE_2__* connector_funcs; struct drm_connector* external_connector; int /*<<< orphan*/  crtc; } ;
struct drm_display_mode {int dummy; } ;
struct drm_connector {TYPE_1__* dev; } ;
struct TYPE_4__ {int (* mode_valid ) (struct drm_connector*,struct drm_display_mode*) ;} ;
struct TYPE_3__ {struct tilcdc_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IS_ERR (TYPE_2__*) ; 
 int MODE_OK ; 
 int stub1 (struct drm_connector*,struct drm_display_mode*) ; 
 int tilcdc_crtc_mode_valid (int /*<<< orphan*/ ,struct drm_display_mode*) ; 

__attribute__((used)) static int tilcdc_external_mode_valid(struct drm_connector *connector,
				      struct drm_display_mode *mode)
{
	struct tilcdc_drm_private *priv = connector->dev->dev_private;
	int ret;

	ret = tilcdc_crtc_mode_valid(priv->crtc, mode);
	if (ret != MODE_OK)
		return ret;

	BUG_ON(priv->external_connector != connector);
	BUG_ON(!priv->connector_funcs);

	/* If the connector has its own mode_valid call it. */
	if (!IS_ERR(priv->connector_funcs) &&
	    priv->connector_funcs->mode_valid)
		return priv->connector_funcs->mode_valid(connector, mode);

	return MODE_OK;
}