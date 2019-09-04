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
struct media_graph {size_t top; TYPE_1__* stack; } ;
struct media_entity {int dummy; } ;
struct TYPE_2__ {struct media_entity* entity; } ;

/* Variables and functions */

__attribute__((used)) static struct media_entity *stack_pop(struct media_graph *graph)
{
	struct media_entity *entity;

	entity = graph->stack[graph->top].entity;
	graph->top--;

	return entity;
}