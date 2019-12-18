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
struct dpi_data {int dss_model; int /*<<< orphan*/  id; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  DSSWARN (char*) ; 
#define  DSS_MODEL_DRA7 132 
#define  DSS_MODEL_OMAP2 131 
#define  DSS_MODEL_OMAP3 130 
#define  DSS_MODEL_OMAP4 129 
#define  DSS_MODEL_OMAP5 128 
 int OMAP_DSS_CHANNEL_LCD ; 
 int OMAP_DSS_CHANNEL_LCD2 ; 
 int OMAP_DSS_CHANNEL_LCD3 ; 

__attribute__((used)) static enum omap_channel dpi_get_channel(struct dpi_data *dpi)
{
	switch (dpi->dss_model) {
	case DSS_MODEL_OMAP2:
	case DSS_MODEL_OMAP3:
		return OMAP_DSS_CHANNEL_LCD;

	case DSS_MODEL_DRA7:
		switch (dpi->id) {
		case 2:
			return OMAP_DSS_CHANNEL_LCD3;
		case 1:
			return OMAP_DSS_CHANNEL_LCD2;
		case 0:
		default:
			return OMAP_DSS_CHANNEL_LCD;
		}

	case DSS_MODEL_OMAP4:
		return OMAP_DSS_CHANNEL_LCD2;

	case DSS_MODEL_OMAP5:
		return OMAP_DSS_CHANNEL_LCD3;

	default:
		DSSWARN("unsupported DSS version\n");
		return OMAP_DSS_CHANNEL_LCD;
	}
}