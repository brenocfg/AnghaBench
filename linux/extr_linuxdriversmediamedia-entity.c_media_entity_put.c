#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* mdev; } ;
struct media_entity {TYPE_4__ graph_obj; } ;
struct TYPE_7__ {TYPE_2__* dev; } ;
struct TYPE_6__ {TYPE_1__* driver; } ;
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

void media_entity_put(struct media_entity *entity)
{
	if (entity == NULL)
		return;

	if (entity->graph_obj.mdev->dev)
		module_put(entity->graph_obj.mdev->dev->driver->owner);
}