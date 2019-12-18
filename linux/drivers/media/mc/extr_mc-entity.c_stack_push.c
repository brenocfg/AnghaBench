#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct media_graph {int top; TYPE_2__* stack; } ;
struct TYPE_3__ {int /*<<< orphan*/  next; } ;
struct media_entity {TYPE_1__ links; } ;
struct TYPE_4__ {struct media_entity* entity; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int MEDIA_ENTITY_ENUM_MAX_DEPTH ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void stack_push(struct media_graph *graph,
		       struct media_entity *entity)
{
	if (graph->top == MEDIA_ENTITY_ENUM_MAX_DEPTH - 1) {
		WARN_ON(1);
		return;
	}
	graph->top++;
	graph->stack[graph->top].link = entity->links.next;
	graph->stack[graph->top].entity = entity;
}