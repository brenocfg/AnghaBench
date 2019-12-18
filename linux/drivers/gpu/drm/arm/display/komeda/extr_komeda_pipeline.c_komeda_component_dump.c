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
struct komeda_component {int /*<<< orphan*/  supported_outputs; int /*<<< orphan*/  max_active_outputs; int /*<<< orphan*/  supported_inputs; int /*<<< orphan*/  max_active_inputs; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void komeda_component_dump(struct komeda_component *c)
{
	if (!c)
		return;

	DRM_DEBUG("	%s: ID %d-0x%08lx.\n",
		  c->name, c->id, BIT(c->id));
	DRM_DEBUG("		max_active_inputs:%d, supported_inputs: 0x%08x.\n",
		  c->max_active_inputs, c->supported_inputs);
	DRM_DEBUG("		max_active_outputs:%d, supported_outputs: 0x%08x.\n",
		  c->max_active_outputs, c->supported_outputs);
}