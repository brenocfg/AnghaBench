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
struct sdw_bus {int link_id; int /*<<< orphan*/  debugfs; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdw_debugfs_root ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void sdw_bus_debugfs_init(struct sdw_bus *bus)
{
	char name[16];

	if (!sdw_debugfs_root)
		return;

	/* create the debugfs master-N */
	snprintf(name, sizeof(name), "master-%d", bus->link_id);
	bus->debugfs = debugfs_create_dir(name, sdw_debugfs_root);
}