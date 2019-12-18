#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rproc_subdev {int dummy; } ;
struct qcom_rproc_glink {int /*<<< orphan*/  edge; int /*<<< orphan*/  node; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_glink_smem_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qcom_rproc_glink* to_glink_subdev (struct rproc_subdev*) ; 

__attribute__((used)) static int glink_subdev_start(struct rproc_subdev *subdev)
{
	struct qcom_rproc_glink *glink = to_glink_subdev(subdev);

	glink->edge = qcom_glink_smem_register(glink->dev, glink->node);

	return PTR_ERR_OR_ZERO(glink->edge);
}