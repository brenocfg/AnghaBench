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
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct hantro_func {TYPE_1__ vdev; int /*<<< orphan*/  proc; int /*<<< orphan*/  sink; int /*<<< orphan*/  intf_devnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_device_unregister_entity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_devnode_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_remove_links (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hantro_detach_func(struct hantro_func *func)
{
	media_devnode_remove(func->intf_devnode);
	media_entity_remove_links(&func->sink);
	media_entity_remove_links(&func->proc);
	media_entity_remove_links(&func->vdev.entity);
	media_device_unregister_entity(&func->sink);
	media_device_unregister_entity(&func->proc);
	media_device_unregister_entity(&func->vdev.entity);
}