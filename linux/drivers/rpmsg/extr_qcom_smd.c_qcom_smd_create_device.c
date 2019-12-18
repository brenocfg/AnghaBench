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
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct rpmsg_device {TYPE_2__ dev; void* dst; void* src; TYPE_1__ id; int /*<<< orphan*/ * ops; } ;
struct qcom_smd_edge {int /*<<< orphan*/  dev; int /*<<< orphan*/  of_node; } ;
struct qcom_smd_device {struct rpmsg_device rpdev; struct qcom_smd_edge* edge; } ;
struct qcom_smd_channel {int /*<<< orphan*/  name; struct qcom_smd_edge* edge; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* RPMSG_ADDR_ANY ; 
 int /*<<< orphan*/  RPMSG_NAME_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct qcom_smd_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_smd_device_ops ; 
 int /*<<< orphan*/  qcom_smd_match_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_smd_release_device ; 
 int rpmsg_register_device (struct rpmsg_device*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_smd_create_device(struct qcom_smd_channel *channel)
{
	struct qcom_smd_device *qsdev;
	struct rpmsg_device *rpdev;
	struct qcom_smd_edge *edge = channel->edge;

	dev_dbg(&edge->dev, "registering '%s'\n", channel->name);

	qsdev = kzalloc(sizeof(*qsdev), GFP_KERNEL);
	if (!qsdev)
		return -ENOMEM;

	/* Link qsdev to our SMD edge */
	qsdev->edge = edge;

	/* Assign callbacks for rpmsg_device */
	qsdev->rpdev.ops = &qcom_smd_device_ops;

	/* Assign public information to the rpmsg_device */
	rpdev = &qsdev->rpdev;
	strncpy(rpdev->id.name, channel->name, RPMSG_NAME_SIZE);
	rpdev->src = RPMSG_ADDR_ANY;
	rpdev->dst = RPMSG_ADDR_ANY;

	rpdev->dev.of_node = qcom_smd_match_channel(edge->of_node, channel->name);
	rpdev->dev.parent = &edge->dev;
	rpdev->dev.release = qcom_smd_release_device;

	return rpmsg_register_device(rpdev);
}