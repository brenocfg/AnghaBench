#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  polled; } ;
struct tfp410 {TYPE_1__ connector; int /*<<< orphan*/  dev; scalar_t__ hpd; } ;
struct drm_bridge {int /*<<< orphan*/  encoder; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_HDMIA ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct tfp410* drm_bridge_to_tfp410 (struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfp410_con_funcs ; 
 int /*<<< orphan*/  tfp410_con_helper_funcs ; 

__attribute__((used)) static int tfp410_attach(struct drm_bridge *bridge)
{
	struct tfp410 *dvi = drm_bridge_to_tfp410(bridge);
	int ret;

	if (!bridge->encoder) {
		dev_err(dvi->dev, "Missing encoder\n");
		return -ENODEV;
	}

	if (dvi->hpd)
		dvi->connector.polled = DRM_CONNECTOR_POLL_HPD;

	drm_connector_helper_add(&dvi->connector,
				 &tfp410_con_helper_funcs);
	ret = drm_connector_init(bridge->dev, &dvi->connector,
				 &tfp410_con_funcs, DRM_MODE_CONNECTOR_HDMIA);
	if (ret) {
		dev_err(dvi->dev, "drm_connector_init() failed: %d\n", ret);
		return ret;
	}

	drm_connector_attach_encoder(&dvi->connector,
					  bridge->encoder);

	return 0;
}