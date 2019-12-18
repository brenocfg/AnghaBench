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
struct ib_uflow_resources {size_t max; struct ib_uflow_resources* counters; void* collection; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_uflow_resources*) ; 
 struct ib_uflow_resources* kzalloc (int,int /*<<< orphan*/ ) ; 

struct ib_uflow_resources *flow_resources_alloc(size_t num_specs)
{
	struct ib_uflow_resources *resources;

	resources = kzalloc(sizeof(*resources), GFP_KERNEL);

	if (!resources)
		return NULL;

	if (!num_specs)
		goto out;

	resources->counters =
		kcalloc(num_specs, sizeof(*resources->counters), GFP_KERNEL);
	resources->collection =
		kcalloc(num_specs, sizeof(*resources->collection), GFP_KERNEL);

	if (!resources->counters || !resources->collection)
		goto err;

out:
	resources->max = num_specs;
	return resources;

err:
	kfree(resources->counters);
	kfree(resources);

	return NULL;
}