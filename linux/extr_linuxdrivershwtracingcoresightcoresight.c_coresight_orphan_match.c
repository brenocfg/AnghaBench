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
struct coresight_device {int orphan; int nr_outport; int /*<<< orphan*/  dev; struct coresight_connection* conns; } ;
struct coresight_connection {struct coresight_device* child_dev; scalar_t__ child_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,scalar_t__) ; 
 struct coresight_device* to_coresight_device (struct device*) ; 

__attribute__((used)) static int coresight_orphan_match(struct device *dev, void *data)
{
	int i;
	bool still_orphan = false;
	struct coresight_device *csdev, *i_csdev;
	struct coresight_connection *conn;

	csdev = data;
	i_csdev = to_coresight_device(dev);

	/* No need to check oneself */
	if (csdev == i_csdev)
		return 0;

	/* Move on to another component if no connection is orphan */
	if (!i_csdev->orphan)
		return 0;
	/*
	 * Circle throuch all the connection of that component.  If we find
	 * an orphan connection whose name matches @csdev, link it.
	 */
	for (i = 0; i < i_csdev->nr_outport; i++) {
		conn = &i_csdev->conns[i];

		/* We have found at least one orphan connection */
		if (conn->child_dev == NULL) {
			/* Does it match this newly added device? */
			if (conn->child_name &&
			    !strcmp(dev_name(&csdev->dev), conn->child_name)) {
				conn->child_dev = csdev;
			} else {
				/* This component still has an orphan */
				still_orphan = true;
			}
		}
	}

	i_csdev->orphan = still_orphan;

	/*
	 * Returning '0' ensures that all known component on the
	 * bus will be checked.
	 */
	return 0;
}