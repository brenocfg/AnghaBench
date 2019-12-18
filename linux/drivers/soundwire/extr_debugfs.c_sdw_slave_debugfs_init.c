#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sdw_slave {struct dentry* debugfs; int /*<<< orphan*/  dev; TYPE_1__* bus; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {struct dentry* debugfs; } ;

/* Variables and functions */
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct sdw_slave*,int /*<<< orphan*/ *) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdw_slave_reg_fops ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

void sdw_slave_debugfs_init(struct sdw_slave *slave)
{
	struct dentry *master;
	struct dentry *d;
	char name[32];

	master = slave->bus->debugfs;

	/* create the debugfs slave-name */
	snprintf(name, sizeof(name), "%s", dev_name(&slave->dev));
	d = debugfs_create_dir(name, master);

	debugfs_create_file("registers", 0400, d, slave, &sdw_slave_reg_fops);

	slave->debugfs = d;
}