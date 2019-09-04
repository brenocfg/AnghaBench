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
struct tilcdc_drm_private {struct drm_connector_helper_funcs* connector_funcs; struct drm_connector* external_connector; } ;
struct drm_device {int /*<<< orphan*/  dev; struct tilcdc_drm_private* dev_private; } ;
struct drm_connector_helper_funcs {int /*<<< orphan*/  mode_valid; } ;
struct drm_connector {int /*<<< orphan*/  name; struct drm_connector_helper_funcs* helper_private; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int ENOMEM ; 
 struct drm_connector_helper_funcs* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (struct drm_connector*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct drm_connector_helper_funcs* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,struct drm_connector_helper_funcs*) ; 
 int /*<<< orphan*/  tilcdc_external_mode_valid ; 

__attribute__((used)) static int tilcdc_add_external_connector(struct drm_device *dev,
					 struct drm_connector *connector)
{
	struct tilcdc_drm_private *priv = dev->dev_private;
	struct drm_connector_helper_funcs *connector_funcs;

	/* There should never be more than one connector */
	if (WARN_ON(priv->external_connector))
		return -EINVAL;

	priv->external_connector = connector;
	connector_funcs = devm_kzalloc(dev->dev, sizeof(*connector_funcs),
				       GFP_KERNEL);
	if (!connector_funcs)
		return -ENOMEM;

	/* connector->helper_private contains always struct
	 * connector_helper_funcs pointer. For tilcdc crtc to have a
	 * say if a specific mode is Ok, we need to install our own
	 * helper functions. In our helper functions we copy
	 * everything else but use our own mode_valid() (above).
	 */
	if (connector->helper_private) {
		priv->connector_funcs =	connector->helper_private;
		*connector_funcs = *priv->connector_funcs;
	} else {
		priv->connector_funcs = ERR_PTR(-ENOENT);
	}
	connector_funcs->mode_valid = tilcdc_external_mode_valid;
	drm_connector_helper_add(connector, connector_funcs);

	dev_dbg(dev->dev, "External connector '%s' connected\n",
		connector->name);

	return 0;
}