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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int bus_width; int flags; } ;
struct TYPE_5__ {TYPE_1__ parallel; } ;
struct v4l2_fwnode_endpoint {TYPE_2__ bus; int /*<<< orphan*/  bus_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  fwnode; } ;
struct v4l2_async_subdev {TYPE_3__ match; int /*<<< orphan*/  match_type; } ;
struct pxa_camera_dev {int platform_flags; int /*<<< orphan*/  mclk; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int PXA_CAMERA_DATAWIDTH_10 ; 
 int PXA_CAMERA_DATAWIDTH_4 ; 
 int PXA_CAMERA_DATAWIDTH_5 ; 
 int PXA_CAMERA_DATAWIDTH_8 ; 
 int PXA_CAMERA_DATAWIDTH_9 ; 
 int PXA_CAMERA_HSP ; 
 int PXA_CAMERA_MASTER ; 
 int PXA_CAMERA_MCLK_EN ; 
 int PXA_CAMERA_PCLK_EN ; 
 int PXA_CAMERA_PCP ; 
 int PXA_CAMERA_VSP ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 int V4L2_MBUS_HSYNC_ACTIVE_HIGH ; 
 int V4L2_MBUS_MASTER ; 
 int V4L2_MBUS_PCLK_SAMPLE_FALLING ; 
 int V4L2_MBUS_PCLK_SAMPLE_RISING ; 
 int V4L2_MBUS_VSYNC_ACTIVE_HIGH ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_notice (struct device*,char*,struct device_node*) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (struct device_node*,int /*<<< orphan*/ *) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int pxa_camera_pdata_from_dt(struct device *dev,
				    struct pxa_camera_dev *pcdev,
				    struct v4l2_async_subdev *asd)
{
	u32 mclk_rate;
	struct device_node *remote, *np = dev->of_node;
	struct v4l2_fwnode_endpoint ep = { .bus_type = 0 };
	int err = of_property_read_u32(np, "clock-frequency",
				       &mclk_rate);
	if (!err) {
		pcdev->platform_flags |= PXA_CAMERA_MCLK_EN;
		pcdev->mclk = mclk_rate;
	}

	np = of_graph_get_next_endpoint(np, NULL);
	if (!np) {
		dev_err(dev, "could not find endpoint\n");
		return -EINVAL;
	}

	err = v4l2_fwnode_endpoint_parse(of_fwnode_handle(np), &ep);
	if (err) {
		dev_err(dev, "could not parse endpoint\n");
		goto out;
	}

	switch (ep.bus.parallel.bus_width) {
	case 4:
		pcdev->platform_flags |= PXA_CAMERA_DATAWIDTH_4;
		break;
	case 5:
		pcdev->platform_flags |= PXA_CAMERA_DATAWIDTH_5;
		break;
	case 8:
		pcdev->platform_flags |= PXA_CAMERA_DATAWIDTH_8;
		break;
	case 9:
		pcdev->platform_flags |= PXA_CAMERA_DATAWIDTH_9;
		break;
	case 10:
		pcdev->platform_flags |= PXA_CAMERA_DATAWIDTH_10;
		break;
	default:
		break;
	}

	if (ep.bus.parallel.flags & V4L2_MBUS_MASTER)
		pcdev->platform_flags |= PXA_CAMERA_MASTER;
	if (ep.bus.parallel.flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
		pcdev->platform_flags |= PXA_CAMERA_HSP;
	if (ep.bus.parallel.flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
		pcdev->platform_flags |= PXA_CAMERA_VSP;
	if (ep.bus.parallel.flags & V4L2_MBUS_PCLK_SAMPLE_RISING)
		pcdev->platform_flags |= PXA_CAMERA_PCLK_EN | PXA_CAMERA_PCP;
	if (ep.bus.parallel.flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
		pcdev->platform_flags |= PXA_CAMERA_PCLK_EN;

	asd->match_type = V4L2_ASYNC_MATCH_FWNODE;
	remote = of_graph_get_remote_port_parent(np);
	if (remote)
		asd->match.fwnode = of_fwnode_handle(remote);
	else
		dev_notice(dev, "no remote for %pOF\n", np);

out:
	of_node_put(np);

	return err;
}