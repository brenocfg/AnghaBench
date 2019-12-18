#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* data_lanes; int* lane_polarities; int num_data_lanes; } ;
struct TYPE_5__ {TYPE_1__ mipi_csi2; } ;
struct v4l2_fwnode_endpoint {TYPE_2__ bus; } ;
struct TYPE_6__ {int mode_reg1; } ;
struct mipid02_dev {TYPE_3__ r; struct v4l2_fwnode_endpoint rx; } ;

/* Variables and functions */
 int MODE_DATA_SWAP ; 
 int mipid02_configure_clk_lane (struct mipid02_dev*) ; 
 int mipid02_configure_data0_lane (struct mipid02_dev*,int,int,int*) ; 
 int mipid02_configure_data1_lane (struct mipid02_dev*,int,int,int*) ; 
 int mipid02_configure_from_rx_speed (struct mipid02_dev*) ; 

__attribute__((used)) static int mipid02_configure_from_rx(struct mipid02_dev *bridge)
{
	struct v4l2_fwnode_endpoint *ep = &bridge->rx;
	bool are_lanes_swap = ep->bus.mipi_csi2.data_lanes[0] == 2;
	bool *polarities = ep->bus.mipi_csi2.lane_polarities;
	int nb = ep->bus.mipi_csi2.num_data_lanes;
	int ret;

	ret = mipid02_configure_clk_lane(bridge);
	if (ret)
		return ret;

	ret = mipid02_configure_data0_lane(bridge, nb, are_lanes_swap,
					   polarities);
	if (ret)
		return ret;

	ret = mipid02_configure_data1_lane(bridge, nb, are_lanes_swap,
					   polarities);
	if (ret)
		return ret;

	bridge->r.mode_reg1 |= are_lanes_swap ? MODE_DATA_SWAP : 0;
	bridge->r.mode_reg1 |= (nb - 1) << 1;

	return mipid02_configure_from_rx_speed(bridge);
}