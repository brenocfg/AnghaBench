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
struct media_graph {int /*<<< orphan*/  ent_enum; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_enum_cleanup (int /*<<< orphan*/ *) ; 

void media_graph_walk_cleanup(struct media_graph *graph)
{
	media_entity_enum_cleanup(&graph->ent_enum);
}