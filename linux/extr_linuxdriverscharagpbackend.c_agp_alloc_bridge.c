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
struct agp_bridge_data {int /*<<< orphan*/  current_memory_agp; int /*<<< orphan*/  agp_in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct agp_bridge_data* agp_bridge ; 
 int /*<<< orphan*/  agp_bridges ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct agp_bridge_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

struct agp_bridge_data *agp_alloc_bridge(void)
{
	struct agp_bridge_data *bridge;

	bridge = kzalloc(sizeof(*bridge), GFP_KERNEL);
	if (!bridge)
		return NULL;

	atomic_set(&bridge->agp_in_use, 0);
	atomic_set(&bridge->current_memory_agp, 0);

	if (list_empty(&agp_bridges))
		agp_bridge = bridge;

	return bridge;
}