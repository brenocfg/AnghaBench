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
struct ocelot_port_block {TYPE_2__* port; } ;
struct ocelot_ace_rule {int dummy; } ;
struct flow_cls_offload {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  offload_cnt; } ;
struct TYPE_4__ {TYPE_1__ tc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kfree (struct ocelot_ace_rule*) ; 
 struct ocelot_ace_rule* ocelot_ace_rule_create (struct flow_cls_offload*,struct ocelot_port_block*) ; 
 int ocelot_ace_rule_offload_add (struct ocelot_ace_rule*) ; 
 int ocelot_flower_parse (struct flow_cls_offload*,struct ocelot_ace_rule*) ; 

__attribute__((used)) static int ocelot_flower_replace(struct flow_cls_offload *f,
				 struct ocelot_port_block *port_block)
{
	struct ocelot_ace_rule *rule;
	int ret;

	rule = ocelot_ace_rule_create(f, port_block);
	if (!rule)
		return -ENOMEM;

	ret = ocelot_flower_parse(f, rule);
	if (ret) {
		kfree(rule);
		return ret;
	}

	ret = ocelot_ace_rule_offload_add(rule);
	if (ret)
		return ret;

	port_block->port->tc.offload_cnt++;
	return 0;
}