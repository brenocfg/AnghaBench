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
struct ocelot_port_block {int /*<<< orphan*/  port; } ;
struct TYPE_3__ {int /*<<< orphan*/  pkts; } ;
struct ocelot_ace_rule {TYPE_1__ stats; int /*<<< orphan*/  id; int /*<<< orphan*/  port; int /*<<< orphan*/  prio; } ;
struct TYPE_4__ {int /*<<< orphan*/  prio; } ;
struct flow_cls_offload {int /*<<< orphan*/  stats; int /*<<< orphan*/  cookie; TYPE_2__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  flow_stats_update (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int ocelot_ace_rule_stats_update (struct ocelot_ace_rule*) ; 

__attribute__((used)) static int ocelot_flower_stats_update(struct flow_cls_offload *f,
				      struct ocelot_port_block *port_block)
{
	struct ocelot_ace_rule rule;
	int ret;

	rule.prio = f->common.prio;
	rule.port = port_block->port;
	rule.id = f->cookie;
	ret = ocelot_ace_rule_stats_update(&rule);
	if (ret)
		return ret;

	flow_stats_update(&f->stats, 0x0, rule.stats.pkts, 0x0);
	return 0;
}