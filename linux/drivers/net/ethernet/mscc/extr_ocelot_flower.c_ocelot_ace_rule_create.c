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
struct ocelot_port_block {TYPE_1__* port; } ;
struct ocelot_ace_rule {int /*<<< orphan*/  chip_port; TYPE_1__* port; } ;
struct flow_cls_offload {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ocelot_ace_rule* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
struct ocelot_ace_rule *ocelot_ace_rule_create(struct flow_cls_offload *f,
					       struct ocelot_port_block *block)
{
	struct ocelot_ace_rule *rule;

	rule = kzalloc(sizeof(*rule), GFP_KERNEL);
	if (!rule)
		return NULL;

	rule->port = block->port;
	rule->chip_port = block->port->chip_port;
	return rule;
}