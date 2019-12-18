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
struct dsi_data {int /*<<< orphan*/  module_id; TYPE_1__* data; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_2__ {int model; } ;

/* Variables and functions */
#define  DSI_MODEL_OMAP3 130 
#define  DSI_MODEL_OMAP4 129 
#define  DSI_MODEL_OMAP5 128 
 int /*<<< orphan*/  DSSWARN (char*) ; 
 int OMAP_DSS_CHANNEL_LCD ; 
 int OMAP_DSS_CHANNEL_LCD2 ; 
 int OMAP_DSS_CHANNEL_LCD3 ; 

__attribute__((used)) static enum omap_channel dsi_get_channel(struct dsi_data *dsi)
{
	switch (dsi->data->model) {
	case DSI_MODEL_OMAP3:
		return OMAP_DSS_CHANNEL_LCD;

	case DSI_MODEL_OMAP4:
		switch (dsi->module_id) {
		case 0:
			return OMAP_DSS_CHANNEL_LCD;
		case 1:
			return OMAP_DSS_CHANNEL_LCD2;
		default:
			DSSWARN("unsupported module id\n");
			return OMAP_DSS_CHANNEL_LCD;
		}

	case DSI_MODEL_OMAP5:
		switch (dsi->module_id) {
		case 0:
			return OMAP_DSS_CHANNEL_LCD;
		case 1:
			return OMAP_DSS_CHANNEL_LCD3;
		default:
			DSSWARN("unsupported module id\n");
			return OMAP_DSS_CHANNEL_LCD;
		}

	default:
		DSSWARN("unsupported DSS version\n");
		return OMAP_DSS_CHANNEL_LCD;
	}
}