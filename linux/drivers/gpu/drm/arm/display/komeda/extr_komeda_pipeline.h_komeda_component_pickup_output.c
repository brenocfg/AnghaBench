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
typedef  int u32 ;
struct komeda_component {int supported_outputs; int /*<<< orphan*/  pipeline; } ;

/* Variables and functions */
 struct komeda_component* komeda_pipeline_get_first_component (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct komeda_component *
komeda_component_pickup_output(struct komeda_component *c, u32 avail_comps)
{
	u32 avail_inputs = c->supported_outputs & (avail_comps);

	return komeda_pipeline_get_first_component(c->pipeline, avail_inputs);
}