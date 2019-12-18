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
typedef  int /*<<< orphan*/  del_ace ;
struct TYPE_7__ {int count; } ;
struct TYPE_6__ {int /*<<< orphan*/  ocelot; } ;

/* Variables and functions */
 TYPE_2__* acl_block ; 
 int /*<<< orphan*/  is2_entry_set (int /*<<< orphan*/ ,int,struct ocelot_ace_rule*) ; 
 int /*<<< orphan*/  memset (struct ocelot_ace_rule*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocelot_ace_rule_del (TYPE_2__*,struct ocelot_ace_rule*) ; 
 int ocelot_ace_rule_get_index_id (TYPE_2__*,struct ocelot_ace_rule*) ; 
 struct ocelot_ace_rule* ocelot_ace_rule_get_rule_index (TYPE_2__*,int) ; 

int ocelot_ace_rule_offload_del(struct ocelot_ace_rule *rule)
{
	struct ocelot_ace_rule del_ace;
	struct ocelot_ace_rule *ace;
	int i, index;

	memset(&del_ace, 0, sizeof(del_ace));

	/* Gets index of the rule */
	index = ocelot_ace_rule_get_index_id(acl_block, rule);

	/* Delete rule */
	ocelot_ace_rule_del(acl_block, rule);

	/* Move up all the blocks over the deleted rule */
	for (i = index; i < acl_block->count; i++) {
		ace = ocelot_ace_rule_get_rule_index(acl_block, i);
		is2_entry_set(rule->port->ocelot, i, ace);
	}

	/* Now delete the last rule, because it is duplicated */
	is2_entry_set(rule->port->ocelot, acl_block->count, &del_ace);

	return 0;
}