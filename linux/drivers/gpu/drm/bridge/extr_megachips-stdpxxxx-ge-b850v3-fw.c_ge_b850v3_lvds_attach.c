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
struct i2c_client {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  polled; } ;
struct drm_bridge {int /*<<< orphan*/  encoder; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct i2c_client* stdp4028_i2c; struct drm_connector connector; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DisplayPort ; 
 int ENODEV ; 
 int /*<<< orphan*/  STDP4028_DPTX_DP_IRQ_EN ; 
 int /*<<< orphan*/  STDP4028_DPTX_IRQ_CONFIG ; 
 int /*<<< orphan*/  STDP4028_DPTX_IRQ_EN_REG ; 
 int /*<<< orphan*/  STDP4028_IRQ_OUT_CONF_REG ; 
 int drm_connector_attach_encoder (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (int /*<<< orphan*/ ,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ge_b850v3_lvds_connector_funcs ; 
 int /*<<< orphan*/  ge_b850v3_lvds_connector_helper_funcs ; 
 TYPE_1__* ge_b850v3_lvds_ptr ; 
 int /*<<< orphan*/  i2c_smbus_write_word_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ge_b850v3_lvds_attach(struct drm_bridge *bridge)
{
	struct drm_connector *connector = &ge_b850v3_lvds_ptr->connector;
	struct i2c_client *stdp4028_i2c
			= ge_b850v3_lvds_ptr->stdp4028_i2c;
	int ret;

	if (!bridge->encoder) {
		DRM_ERROR("Parent encoder object not found");
		return -ENODEV;
	}

	connector->polled = DRM_CONNECTOR_POLL_HPD;

	drm_connector_helper_add(connector,
				 &ge_b850v3_lvds_connector_helper_funcs);

	ret = drm_connector_init(bridge->dev, connector,
				 &ge_b850v3_lvds_connector_funcs,
				 DRM_MODE_CONNECTOR_DisplayPort);
	if (ret) {
		DRM_ERROR("Failed to initialize connector with drm\n");
		return ret;
	}

	ret = drm_connector_attach_encoder(connector, bridge->encoder);
	if (ret)
		return ret;

	/* Configures the bridge to re-enable interrupts after each ack. */
	i2c_smbus_write_word_data(stdp4028_i2c,
				  STDP4028_IRQ_OUT_CONF_REG,
				  STDP4028_DPTX_DP_IRQ_EN);

	/* Enable interrupts */
	i2c_smbus_write_word_data(stdp4028_i2c,
				  STDP4028_DPTX_IRQ_EN_REG,
				  STDP4028_DPTX_IRQ_CONFIG);

	return 0;
}