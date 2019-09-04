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
typedef  scalar_t__ u32 ;
struct v4l2_fwnode_bus_mipi_csi1 {scalar_t__ clock_lane; scalar_t__ data_lane; scalar_t__ strobe; scalar_t__ clock_inv; } ;
struct TYPE_2__ {struct v4l2_fwnode_bus_mipi_csi1 mipi_csi1; } ;
struct v4l2_fwnode_endpoint {int /*<<< orphan*/  bus_type; TYPE_1__ bus; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 scalar_t__ V4L2_FWNODE_BUS_TYPE_CCP2 ; 
 int /*<<< orphan*/  V4L2_MBUS_CCP2 ; 
 int /*<<< orphan*/  V4L2_MBUS_CSI1 ; 
 int /*<<< orphan*/  fwnode_property_read_u32 (struct fwnode_handle*,char*,scalar_t__*) ; 

__attribute__((used)) static void
v4l2_fwnode_endpoint_parse_csi1_bus(struct fwnode_handle *fwnode,
				    struct v4l2_fwnode_endpoint *vep,
				    u32 bus_type)
{
	struct v4l2_fwnode_bus_mipi_csi1 *bus = &vep->bus.mipi_csi1;
	u32 v;

	if (!fwnode_property_read_u32(fwnode, "clock-inv", &v))
		bus->clock_inv = v;

	if (!fwnode_property_read_u32(fwnode, "strobe", &v))
		bus->strobe = v;

	if (!fwnode_property_read_u32(fwnode, "data-lanes", &v))
		bus->data_lane = v;

	if (!fwnode_property_read_u32(fwnode, "clock-lanes", &v))
		bus->clock_lane = v;

	if (bus_type == V4L2_FWNODE_BUS_TYPE_CCP2)
		vep->bus_type = V4L2_MBUS_CCP2;
	else
		vep->bus_type = V4L2_MBUS_CSI1;
}