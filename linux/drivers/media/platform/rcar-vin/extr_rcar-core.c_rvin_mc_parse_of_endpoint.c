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
struct TYPE_7__ {int port; size_t id; } ;
struct v4l2_fwnode_endpoint {TYPE_3__ base; } ;
struct TYPE_6__ {scalar_t__ fwnode; } ;
struct v4l2_async_subdev {TYPE_2__ match; } ;
struct rvin_dev {TYPE_4__* group; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; TYPE_1__* csi; } ;
struct TYPE_5__ {scalar_t__ fwnode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 size_t RVIN_CSI_MAX ; 
 struct rvin_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_is_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_of_node (scalar_t__) ; 
 int /*<<< orphan*/  vin_dbg (struct rvin_dev*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int rvin_mc_parse_of_endpoint(struct device *dev,
				     struct v4l2_fwnode_endpoint *vep,
				     struct v4l2_async_subdev *asd)
{
	struct rvin_dev *vin = dev_get_drvdata(dev);
	int ret = 0;

	if (vep->base.port != 1 || vep->base.id >= RVIN_CSI_MAX)
		return -EINVAL;

	if (!of_device_is_available(to_of_node(asd->match.fwnode))) {
		vin_dbg(vin, "OF device %pOF disabled, ignoring\n",
			to_of_node(asd->match.fwnode));
		return -ENOTCONN;
	}

	mutex_lock(&vin->group->lock);

	if (vin->group->csi[vep->base.id].fwnode) {
		vin_dbg(vin, "OF device %pOF already handled\n",
			to_of_node(asd->match.fwnode));
		ret = -ENOTCONN;
		goto out;
	}

	vin->group->csi[vep->base.id].fwnode = asd->match.fwnode;

	vin_dbg(vin, "Add group OF device %pOF to slot %u\n",
		to_of_node(asd->match.fwnode), vep->base.id);
out:
	mutex_unlock(&vin->group->lock);

	return ret;
}