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
struct device {int dummy; } ;
struct coresight_device {int nr_outport; int orphan; int /*<<< orphan*/  dev; struct coresight_connection* conns; } ;
struct coresight_connection {int /*<<< orphan*/ * child_dev; int /*<<< orphan*/  child_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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
	for (i = 0; i < iterator->nr_outport; i++) {
		conn = &iterator->conns[i];

		if (conn->child_dev == NULL)
			continue;

		if (!strcmp(dev_name(&csdev->dev), conn->child_name)) {
			iterator->orphan = true;
			conn->child_dev = NULL;
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