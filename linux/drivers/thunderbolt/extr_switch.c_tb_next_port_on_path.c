#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tb_port {scalar_t__ link_nr; struct tb_port* dual_link_port; TYPE_2__* sw; struct tb_port* remote; } ;
struct TYPE_5__ {scalar_t__ depth; } ;
struct TYPE_6__ {TYPE_1__ config; } ;

/* Variables and functions */
 scalar_t__ tb_is_upstream_port (struct tb_port*) ; 
 struct tb_port* tb_port_at (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  tb_route (TYPE_2__*) ; 
 struct tb_port* tb_upstream_port (TYPE_2__*) ; 

struct tb_port *tb_next_port_on_path(struct tb_port *start, struct tb_port *end,
				     struct tb_port *prev)
{
	struct tb_port *next;

	if (!prev)
		return start;

	if (prev->sw == end->sw) {
		if (prev == end)
			return NULL;
		return end;
	}

	if (start->sw->config.depth < end->sw->config.depth) {
		if (prev->remote &&
		    prev->remote->sw->config.depth > prev->sw->config.depth)
			next = prev->remote;
		else
			next = tb_port_at(tb_route(end->sw), prev->sw);
	} else {
		if (tb_is_upstream_port(prev)) {
			next = prev->remote;
		} else {
			next = tb_upstream_port(prev->sw);
			/*
			 * Keep the same link if prev and next are both
			 * dual link ports.
			 */
			if (next->dual_link_port &&
			    next->link_nr != prev->link_nr) {
				next = next->dual_link_port;
			}
		}
	}

	return next;
}