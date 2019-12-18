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
struct TYPE_2__ {scalar_t__ id; scalar_t__ port; } ;
struct v4l2_fwnode_endpoint {int bus_type; TYPE_1__ base; } ;
struct v4l2_async_subdev {int dummy; } ;
struct sun6i_csi {struct v4l2_fwnode_endpoint v4l2_ep; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOTCONN ; 
#define  V4L2_MBUS_BT656 129 
#define  V4L2_MBUS_PARALLEL 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct sun6i_csi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 

__attribute__((used)) static int sun6i_csi_fwnode_parse(struct device *dev,
				  struct v4l2_fwnode_endpoint *vep,
				  struct v4l2_async_subdev *asd)
{
	struct sun6i_csi *csi = dev_get_drvdata(dev);

	if (vep->base.port || vep->base.id) {
		dev_warn(dev, "Only support a single port with one endpoint\n");
		return -ENOTCONN;
	}

	switch (vep->bus_type) {
	case V4L2_MBUS_PARALLEL:
	case V4L2_MBUS_BT656:
		csi->v4l2_ep = *vep;
		return 0;
	default:
		dev_err(dev, "Unsupported media bus type\n");
		return -ENOTCONN;
	}
}