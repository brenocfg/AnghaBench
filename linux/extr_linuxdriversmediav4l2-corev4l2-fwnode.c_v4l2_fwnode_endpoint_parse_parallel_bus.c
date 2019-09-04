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
struct v4l2_fwnode_bus_parallel {unsigned int flags; void* data_shift; void* bus_width; } ;
struct TYPE_2__ {struct v4l2_fwnode_bus_parallel parallel; } ;
struct v4l2_fwnode_endpoint {int /*<<< orphan*/  bus_type; TYPE_1__ bus; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_MBUS_BT656 ; 
 unsigned int V4L2_MBUS_DATA_ACTIVE_HIGH ; 
 unsigned int V4L2_MBUS_DATA_ACTIVE_LOW ; 
 unsigned int V4L2_MBUS_DATA_ENABLE_HIGH ; 
 unsigned int V4L2_MBUS_DATA_ENABLE_LOW ; 
 unsigned int V4L2_MBUS_FIELD_EVEN_HIGH ; 
 unsigned int V4L2_MBUS_FIELD_EVEN_LOW ; 
 unsigned int V4L2_MBUS_HSYNC_ACTIVE_HIGH ; 
 unsigned int V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
 unsigned int V4L2_MBUS_MASTER ; 
 int /*<<< orphan*/  V4L2_MBUS_PARALLEL ; 
 unsigned int V4L2_MBUS_PCLK_SAMPLE_FALLING ; 
 unsigned int V4L2_MBUS_PCLK_SAMPLE_RISING ; 
 unsigned int V4L2_MBUS_SLAVE ; 
 unsigned int V4L2_MBUS_VIDEO_SOG_ACTIVE_HIGH ; 
 unsigned int V4L2_MBUS_VIDEO_SOG_ACTIVE_LOW ; 
 unsigned int V4L2_MBUS_VSYNC_ACTIVE_HIGH ; 
 unsigned int V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
 scalar_t__ fwnode_property_present (struct fwnode_handle*,char*) ; 
 int /*<<< orphan*/  fwnode_property_read_u32 (struct fwnode_handle*,char*,void**) ; 

__attribute__((used)) static void v4l2_fwnode_endpoint_parse_parallel_bus(
	struct fwnode_handle *fwnode, struct v4l2_fwnode_endpoint *vep)
{
	struct v4l2_fwnode_bus_parallel *bus = &vep->bus.parallel;
	unsigned int flags = 0;
	u32 v;

	if (!fwnode_property_read_u32(fwnode, "hsync-active", &v))
		flags |= v ? V4L2_MBUS_HSYNC_ACTIVE_HIGH :
			V4L2_MBUS_HSYNC_ACTIVE_LOW;

	if (!fwnode_property_read_u32(fwnode, "vsync-active", &v))
		flags |= v ? V4L2_MBUS_VSYNC_ACTIVE_HIGH :
			V4L2_MBUS_VSYNC_ACTIVE_LOW;

	if (!fwnode_property_read_u32(fwnode, "field-even-active", &v))
		flags |= v ? V4L2_MBUS_FIELD_EVEN_HIGH :
			V4L2_MBUS_FIELD_EVEN_LOW;
	if (flags)
		vep->bus_type = V4L2_MBUS_PARALLEL;
	else
		vep->bus_type = V4L2_MBUS_BT656;

	if (!fwnode_property_read_u32(fwnode, "pclk-sample", &v))
		flags |= v ? V4L2_MBUS_PCLK_SAMPLE_RISING :
			V4L2_MBUS_PCLK_SAMPLE_FALLING;

	if (!fwnode_property_read_u32(fwnode, "data-active", &v))
		flags |= v ? V4L2_MBUS_DATA_ACTIVE_HIGH :
			V4L2_MBUS_DATA_ACTIVE_LOW;

	if (fwnode_property_present(fwnode, "slave-mode"))
		flags |= V4L2_MBUS_SLAVE;
	else
		flags |= V4L2_MBUS_MASTER;

	if (!fwnode_property_read_u32(fwnode, "bus-width", &v))
		bus->bus_width = v;

	if (!fwnode_property_read_u32(fwnode, "data-shift", &v))
		bus->data_shift = v;

	if (!fwnode_property_read_u32(fwnode, "sync-on-green-active", &v))
		flags |= v ? V4L2_MBUS_VIDEO_SOG_ACTIVE_HIGH :
			V4L2_MBUS_VIDEO_SOG_ACTIVE_LOW;

	if (!fwnode_property_read_u32(fwnode, "data-enable-active", &v))
		flags |= v ? V4L2_MBUS_DATA_ENABLE_HIGH :
			V4L2_MBUS_DATA_ENABLE_LOW;

	bus->flags = flags;

}