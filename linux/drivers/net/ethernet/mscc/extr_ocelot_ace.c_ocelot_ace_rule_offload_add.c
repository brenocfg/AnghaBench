#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ocelot_ace_rule {TYPE_1__* port; } ;
struct TYPE_7__ {int count; } ;
struct TYPE_6__ {int /*<<< orphan*/  ocelot; } ;

/* Variables and functions */
 TYPE_2__* acl_block ; 
 int /*<<< orphan*/  is2_entry_set (int /*<<< orphan*/ ,int,struct ocelot_ace_rule*) ; 
 int /*<<< orphan*/  ocelot_ace_rule_add (TYPE_2__*,struct ocelot_ace_rule*) ; 
 int ocelot_ace_rule_get_index_id (TYPE_2__*,struct ocelot_ace_rule*) ; 
 struct ocelot_ace_rule* ocelot_ace_rule_get_rule_index (TYPE_2__*,int) ; 

int ocelot_ace_rule_offload_add(struct ocelot_ace_rule *rule)
{
	struct ocelot_ace_rule *ace;
	int i, index;

	/* Add rule to the linked list */
	ocelot_ace_rule_add(acl_block, rule);

	/* Get the index of the inserted rule */
	index = ocelot_ace_rule_get_index_id(acl_block, rule);

	/* Move down the rules to make place for the new rule */
	for (i = acl_block->count - 1; i > index; i--) {
		ace = ocelot_ace_rule_get_rule_index(acl_block, i);
		is2_entry_set(rule->port->ocelot, i, ace);
	}

	/* Now insert the new rule */
	is2_entry_set(rule->port->ocelot, index, rule);
	return 0;
}