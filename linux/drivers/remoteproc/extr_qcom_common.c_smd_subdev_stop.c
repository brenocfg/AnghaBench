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
struct qcom_rproc_subdev {int /*<<< orphan*/ * edge; } ;

/* Variables and functions */
 int /*<<< orphan*/  qcom_smd_unregister_edge (int /*<<< orphan*/ *) ; 
 struct qcom_rproc_subdev* to_smd_subdev (struct rproc_subdev*) ; 

__attribute__((used)) static void smd_subdev_stop(struct rproc_subdev *subdev, bool crashed)
{
	struct qcom_rproc_subdev *smd = to_smd_subdev(subdev);

	qcom_smd_unregister_edge(smd->edge);
	smd->edge = NULL;
}