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
typedef  void* u32 ;
struct v4l2_fwnode_bus_mipi_csi1 {void* clock_lane; void* data_lane; void* strobe; void* clock_inv; } ;
struct TYPE_2__ {struct v4l2_fwnode_bus_mipi_csi1 mipi_csi1; } ;
struct v4l2_fwnode_endpoint {int bus_type; TYPE_1__ bus; } ;
struct fwnode_handle {int dummy; } ;
typedef  enum v4l2_mbus_type { ____Placeholder_v4l2_mbus_type } v4l2_mbus_type ;

/* Variables and functions */
 int V4L2_MBUS_CCP2 ; 
 int V4L2_MBUS_CSI1 ; 
 int /*<<< orphan*/  fwnode_property_read_u32 (struct fwnode_handle*,char*,void**) ; 
 int /*<<< orphan*/  pr_debug (char*,void*) ; 

__attribute__((used)) static void
v4l2_fwnode_endpoint_parse_csi1_bus(struct fwnode_handle *fwnode,
				    struct v4l2_fwnode_endpoint *vep,
				    enum v4l2_mbus_type bus_type)
{
	struct v4l2_fwnode_bus_mipi_csi1 *bus = &vep->bus.mipi_csi1;
	u32 v;

	if (!fwnode_property_read_u32(fwnode, "clock-inv", &v)) {
		bus->clock_inv = v;
		pr_debug("clock-inv %u\n", v);
	}

	if (!fwnode_property_read_u32(fwnode, "strobe", &v)) {
		bus->strobe = v;
		pr_debug("strobe %u\n", v);
	}

	if (!fwnode_property_read_u32(fwnode, "data-lanes", &v)) {
		bus->data_lane = v;
		pr_debug("data-lanes %u\n", v);
	}

	if (!fwnode_property_read_u32(fwnode, "clock-lanes", &v)) {
		bus->clock_lane = v;
		pr_debug("clock-lanes %u\n", v);
	}

	if (bus_type == V4L2_MBUS_CCP2)
		vep->bus_type = V4L2_MBUS_CCP2;
	else
		vep->bus_type = V4L2_MBUS_CSI1;
}