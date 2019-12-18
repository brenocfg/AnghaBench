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
struct opp_table {int /*<<< orphan*/  dentry_name; } ;
struct opp_device {int /*<<< orphan*/  dentry; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int NAME_MAX ; 
 int /*<<< orphan*/  debugfs_create_symlink (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opp_set_dev_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rootdir ; 

__attribute__((used)) static void opp_list_debug_create_link(struct opp_device *opp_dev,
				       struct opp_table *opp_table)
{
	char name[NAME_MAX];

	opp_set_dev_name(opp_dev->dev, name);

	/* Create device specific directory link */
	opp_dev->dentry = debugfs_create_symlink(name, rootdir,
						 opp_table->dentry_name);
}