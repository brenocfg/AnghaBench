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
struct fsi_master {int /*<<< orphan*/  scan_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  idx; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  dev_attr_break ; 
 int /*<<< orphan*/  dev_attr_rescan ; 
 struct device_node* dev_of_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsi_master_scan (struct fsi_master*) ; 
 int /*<<< orphan*/  ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  master_ida ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 

int fsi_master_register(struct fsi_master *master)
{
	int rc;
	struct device_node *np;

	mutex_init(&master->scan_lock);
	master->idx = ida_simple_get(&master_ida, 0, INT_MAX, GFP_KERNEL);
	dev_set_name(&master->dev, "fsi%d", master->idx);

	rc = device_register(&master->dev);
	if (rc) {
		ida_simple_remove(&master_ida, master->idx);
		return rc;
	}

	rc = device_create_file(&master->dev, &dev_attr_rescan);
	if (rc) {
		device_del(&master->dev);
		ida_simple_remove(&master_ida, master->idx);
		return rc;
	}

	rc = device_create_file(&master->dev, &dev_attr_break);
	if (rc) {
		device_del(&master->dev);
		ida_simple_remove(&master_ida, master->idx);
		return rc;
	}

	np = dev_of_node(&master->dev);
	if (!of_property_read_bool(np, "no-scan-on-init")) {
		mutex_lock(&master->scan_lock);
		fsi_master_scan(master);
		mutex_unlock(&master->scan_lock);
	}

	return 0;
}