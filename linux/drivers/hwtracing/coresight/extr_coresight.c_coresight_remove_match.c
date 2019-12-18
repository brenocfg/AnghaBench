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
struct device {int dummy; } ;
struct TYPE_4__ {scalar_t__ fwnode; } ;
struct coresight_device {int orphan; TYPE_2__ dev; TYPE_1__* pdata; } ;
struct coresight_connection {scalar_t__ child_fwnode; int /*<<< orphan*/ * child_dev; } ;
struct TYPE_3__ {int nr_outport; struct coresight_connection* conns; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwnode_handle_put (scalar_t__) ; 
 struct coresight_device* to_coresight_device (struct device*) ; 

__attribute__((used)) static int coresight_remove_match(struct device *dev, void *data)
{
	int i;
	struct coresight_device *csdev, *iterator;
	struct coresight_connection *conn;

	csdev = data;
	iterator = to_coresight_device(dev);

	/* No need to check oneself */
	if (csdev == iterator)
		return 0;

	/*
	 * Circle throuch all the connection of that component.  If we find
	 * a connection whose name matches @csdev, remove it.
	 */
	for (i = 0; i < iterator->pdata->nr_outport; i++) {
		conn = &iterator->pdata->conns[i];

		if (conn->child_dev == NULL)
			continue;

		if (csdev->dev.fwnode == conn->child_fwnode) {
			iterator->orphan = true;
			conn->child_dev = NULL;
			/*
			 * Drop the reference to the handle for the remote
			 * device acquired in parsing the connections from
			 * platform data.
			 */
			fwnode_handle_put(conn->child_fwnode);
			/* No need to continue */
			break;
		}
	}

	/*
	 * Returning '0' ensures that all known component on the
	 * bus will be checked.
	 */
	return 0;
}