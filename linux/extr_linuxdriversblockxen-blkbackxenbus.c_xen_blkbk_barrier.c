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
struct xenbus_transaction {int dummy; } ;
struct xenbus_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  nodename; } ;
struct backend_info {struct xenbus_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int xenbus_printf (struct xenbus_transaction,int /*<<< orphan*/ ,char*,char*,int) ; 

int xen_blkbk_barrier(struct xenbus_transaction xbt,
		      struct backend_info *be, int state)
{
	struct xenbus_device *dev = be->dev;
	int err;

	err = xenbus_printf(xbt, dev->nodename, "feature-barrier",
			    "%d", state);
	if (err)
		dev_warn(&dev->dev, "writing feature-barrier (%d)", err);

	return err;
}