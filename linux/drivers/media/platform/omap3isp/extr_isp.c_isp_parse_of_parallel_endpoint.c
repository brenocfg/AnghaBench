#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int /*<<< orphan*/  data_shift; } ;
struct TYPE_6__ {TYPE_1__ parallel; } ;
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; TYPE_2__ bus; } ;
struct TYPE_7__ {int clk_pol; int hs_pol; int vs_pol; int fld_pol; int data_pol; int bt656; int /*<<< orphan*/  data_lane_shift; } ;
struct TYPE_8__ {TYPE_3__ parallel; } ;
struct isp_bus_cfg {TYPE_4__ bus; int /*<<< orphan*/  interface; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_INTERFACE_PARALLEL ; 
 scalar_t__ V4L2_MBUS_BT656 ; 
 int V4L2_MBUS_DATA_ACTIVE_LOW ; 
 int V4L2_MBUS_FIELD_EVEN_LOW ; 
 int V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
 int V4L2_MBUS_PCLK_SAMPLE_FALLING ; 
 int V4L2_MBUS_VSYNC_ACTIVE_LOW ; 

__attribute__((used)) static void isp_parse_of_parallel_endpoint(struct device *dev,
					   struct v4l2_fwnode_endpoint *vep,
					   struct isp_bus_cfg *buscfg)
{
	buscfg->interface = ISP_INTERFACE_PARALLEL;
	buscfg->bus.parallel.data_lane_shift = vep->bus.parallel.data_shift;
	buscfg->bus.parallel.clk_pol =
		!!(vep->bus.parallel.flags & V4L2_MBUS_PCLK_SAMPLE_FALLING);
	buscfg->bus.parallel.hs_pol =
		!!(vep->bus.parallel.flags & V4L2_MBUS_VSYNC_ACTIVE_LOW);
	buscfg->bus.parallel.vs_pol =
		!!(vep->bus.parallel.flags & V4L2_MBUS_HSYNC_ACTIVE_LOW);
	buscfg->bus.parallel.fld_pol =
		!!(vep->bus.parallel.flags & V4L2_MBUS_FIELD_EVEN_LOW);
	buscfg->bus.parallel.data_pol =
		!!(vep->bus.parallel.flags & V4L2_MBUS_DATA_ACTIVE_LOW);
	buscfg->bus.parallel.bt656 = vep->bus_type == V4L2_MBUS_BT656;
}