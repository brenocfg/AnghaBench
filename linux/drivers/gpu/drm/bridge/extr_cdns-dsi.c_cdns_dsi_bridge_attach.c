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
struct drm_bridge {int /*<<< orphan*/  encoder; int /*<<< orphan*/  dev; } ;
struct cdns_dsi_output {int /*<<< orphan*/  bridge; } ;
struct cdns_dsi_input {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct cdns_dsi {TYPE_1__ base; struct cdns_dsi_output output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_ATOMIC ; 
 int ENOTSUPP ; 
 struct cdns_dsi_input* bridge_to_cdns_dsi_input (struct drm_bridge*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int drm_bridge_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_core_check_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cdns_dsi* input_to_dsi (struct cdns_dsi_input*) ; 

__attribute__((used)) static int cdns_dsi_bridge_attach(struct drm_bridge *bridge)
{
	struct cdns_dsi_input *input = bridge_to_cdns_dsi_input(bridge);
	struct cdns_dsi *dsi = input_to_dsi(input);
	struct cdns_dsi_output *output = &dsi->output;

	if (!drm_core_check_feature(bridge->dev, DRIVER_ATOMIC)) {
		dev_err(dsi->base.dev,
			"cdns-dsi driver is only compatible with DRM devices supporting atomic updates");
		return -ENOTSUPP;
	}

	return drm_bridge_attach(bridge->encoder, output->bridge, bridge);
}