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
struct v4l2_fwnode_endpoint {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;
struct v4l2_async_subdev {TYPE_1__ match; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ fwnode_device_is_available (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx7_csi_parse_endpoint(struct device *dev,
				   struct v4l2_fwnode_endpoint *vep,
				   struct v4l2_async_subdev *asd)
{
	return fwnode_device_is_available(asd->match.fwnode) ? 0 : -EINVAL;
}