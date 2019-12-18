#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct media_graph {size_t top; TYPE_3__* stack; int /*<<< orphan*/  ent_enum; } ;
struct TYPE_5__ {TYPE_1__* mdev; } ;
struct media_entity {int /*<<< orphan*/  name; TYPE_2__ graph_obj; } ;
struct TYPE_6__ {int /*<<< orphan*/ * entity; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_enum_set (int /*<<< orphan*/ *,struct media_entity*) ; 
 int /*<<< orphan*/  media_entity_enum_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_push (struct media_graph*,struct media_entity*) ; 

void media_graph_walk_start(struct media_graph *graph,
			    struct media_entity *entity)
{
	media_entity_enum_zero(&graph->ent_enum);
	media_entity_enum_set(&graph->ent_enum, entity);

	graph->top = 0;
	graph->stack[graph->top].entity = NULL;
	stack_push(graph, entity);
	dev_dbg(entity->graph_obj.mdev->dev,
		"begin graph walk at '%s'\n", entity->name);
}