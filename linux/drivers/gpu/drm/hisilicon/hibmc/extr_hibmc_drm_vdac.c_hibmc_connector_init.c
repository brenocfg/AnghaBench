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
struct hibmc_drm_private {struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VGA ; 
 int ENOMEM ; 
 struct drm_connector* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct drm_connector* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hibmc_connector_funcs ; 
 int /*<<< orphan*/  hibmc_connector_helper_funcs ; 

__attribute__((used)) static struct drm_connector *
hibmc_connector_init(struct hibmc_drm_private *priv)
{
	struct drm_device *dev = priv->dev;
	struct drm_connector *connector;
	int ret;

	connector = devm_kzalloc(dev->dev, sizeof(*connector), GFP_KERNEL);
	if (!connector) {
		DRM_ERROR("failed to alloc memory when init connector\n");
		return ERR_PTR(-ENOMEM);
	}

	ret = drm_connector_init(dev, connector,
				 &hibmc_connector_funcs,
				 DRM_MODE_CONNECTOR_VGA);
	if (ret) {
		DRM_ERROR("failed to init connector: %d\n", ret);
		return ERR_PTR(ret);
	}
	drm_connector_helper_add(connector,
				 &hibmc_connector_helper_funcs);

	return connector;
}