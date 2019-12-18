#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int /*<<< orphan*/  grp_id; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct platform_device {int /*<<< orphan*/  id; TYPE_2__ dev; } ;
struct fimc_md {int /*<<< orphan*/  v4l2_dev; TYPE_1__* csis; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int sd; } ;

/* Variables and functions */
 int CSIS_MAX_ENTITIES ; 
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  GRP_ID_CSIS ; 
 scalar_t__ WARN_ON (int) ; 
 int __of_get_csis_id (struct device_node*) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int v4l2_device_register_subdev (int /*<<< orphan*/ *,struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static int register_csis_entity(struct fimc_md *fmd,
				struct platform_device *pdev,
				struct v4l2_subdev *sd)
{
	struct device_node *node = pdev->dev.of_node;
	int id, ret;

	id = node ? __of_get_csis_id(node) : max(0, pdev->id);

	if (WARN_ON(id < 0 || id >= CSIS_MAX_ENTITIES))
		return -ENOENT;

	if (WARN_ON(fmd->csis[id].sd))
		return -EBUSY;

	sd->grp_id = GRP_ID_CSIS;
	ret = v4l2_device_register_subdev(&fmd->v4l2_dev, sd);
	if (!ret)
		fmd->csis[id].sd = sd;
	else
		v4l2_err(&fmd->v4l2_dev,
			 "Failed to register MIPI-CSIS.%d (%d)\n", id, ret);
	return ret;
}