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
struct core_component {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  subsys; } ;

/* Variables and functions */
 int /*<<< orphan*/  configfs_unregister_subsystem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  most_cdev_subsys ; 
 int /*<<< orphan*/  most_net_subsys ; 
 TYPE_1__ most_sound_subsys ; 
 int /*<<< orphan*/  most_video_subsys ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

void most_deregister_configfs_subsys(struct core_component *c)
{
	if (!strcmp(c->name, "cdev"))
		configfs_unregister_subsystem(&most_cdev_subsys);
	else if (!strcmp(c->name, "net"))
		configfs_unregister_subsystem(&most_net_subsys);
	else if (!strcmp(c->name, "video"))
		configfs_unregister_subsystem(&most_video_subsys);
	else if (!strcmp(c->name, "sound"))
		configfs_unregister_subsystem(&most_sound_subsys.subsys);
}