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
typedef  int u32 ;
struct drm_bridge_timings {int input_bus_flags; void* hold_time_ps; void* setup_time_ps; } ;
struct tfp410 {TYPE_1__* dev; int /*<<< orphan*/  bus_format; struct drm_bridge_timings timings; } ;
struct device_node {int dummy; } ;
typedef  int s32 ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int DRM_BUS_FLAG_DE_HIGH ; 
 int DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE ; 
 int DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE ; 
 int DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE ; 
 int DRM_BUS_FLAG_SYNC_SAMPLE_POSEDGE ; 
 int EINVAL ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_RGB888_1X24 ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_RGB888_2X12_LE ; 
 void* min (int /*<<< orphan*/ ,int) ; 
 struct device_node* of_graph_get_endpoint_by_regs (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 struct drm_bridge_timings tfp410_default_timings ; 

__attribute__((used)) static int tfp410_parse_timings(struct tfp410 *dvi, bool i2c)
{
	struct drm_bridge_timings *timings = &dvi->timings;
	struct device_node *ep;
	u32 pclk_sample = 0;
	u32 bus_width = 24;
	s32 deskew = 0;

	/* Start with defaults. */
	*timings = tfp410_default_timings;

	if (i2c)
		/*
		 * In I2C mode timings are configured through the I2C interface.
		 * As the driver doesn't support I2C configuration yet, we just
		 * go with the defaults (BSEL=1, DSEL=1, DKEN=0, EDGE=1).
		 */
		return 0;

	/*
	 * In non-I2C mode, timings are configured through the BSEL, DSEL, DKEN
	 * and EDGE pins. They are specified in DT through endpoint properties
	 * and vendor-specific properties.
	 */
	ep = of_graph_get_endpoint_by_regs(dvi->dev->of_node, 0, 0);
	if (!ep)
		return -EINVAL;

	/* Get the sampling edge from the endpoint. */
	of_property_read_u32(ep, "pclk-sample", &pclk_sample);
	of_property_read_u32(ep, "bus-width", &bus_width);
	of_node_put(ep);

	timings->input_bus_flags = DRM_BUS_FLAG_DE_HIGH;

	switch (pclk_sample) {
	case 0:
		timings->input_bus_flags |= DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE
					 |  DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE;
		break;
	case 1:
		timings->input_bus_flags |= DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE
					 |  DRM_BUS_FLAG_SYNC_SAMPLE_POSEDGE;
		break;
	default:
		return -EINVAL;
	}

	switch (bus_width) {
	case 12:
		dvi->bus_format = MEDIA_BUS_FMT_RGB888_2X12_LE;
		break;
	case 24:
		dvi->bus_format = MEDIA_BUS_FMT_RGB888_1X24;
		break;
	default:
		return -EINVAL;
	}

	/* Get the setup and hold time from vendor-specific properties. */
	of_property_read_u32(dvi->dev->of_node, "ti,deskew", (u32 *)&deskew);
	if (deskew < -4 || deskew > 3)
		return -EINVAL;

	timings->setup_time_ps = min(0, 1200 - 350 * deskew);
	timings->hold_time_ps = min(0, 1300 + 350 * deskew);

	return 0;
}