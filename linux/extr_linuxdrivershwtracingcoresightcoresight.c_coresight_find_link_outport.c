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
struct coresight_device {int nr_outport; int /*<<< orphan*/  dev; struct coresight_connection* conns; } ;
struct coresight_connection {int outport; struct coresight_device* child_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int coresight_find_link_outport(struct coresight_device *csdev,
				       struct coresight_device *child)
{
	int i;
	struct coresight_connection *conn;

	for (i = 0; i < csdev->nr_outport; i++) {
		conn = &csdev->conns[i];
		if (conn->child_dev == child)
			return conn->outport;
	}

	dev_err(&csdev->dev, "couldn't find outport, parent: %s, child: %s\n",
		dev_name(&csdev->dev), dev_name(&child->dev));

	return -ENODEV;
}