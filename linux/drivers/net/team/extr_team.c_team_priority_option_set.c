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
struct team_port {scalar_t__ priority; } ;
struct TYPE_4__ {scalar_t__ s32_val; } ;
struct team_gsetter_ctx {TYPE_2__ data; TYPE_1__* info; } ;
struct team {int dummy; } ;
typedef  scalar_t__ s32 ;
struct TYPE_3__ {struct team_port* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  team_queue_override_port_prio_changed (struct team*,struct team_port*) ; 

__attribute__((used)) static int team_priority_option_set(struct team *team,
				    struct team_gsetter_ctx *ctx)
{
	struct team_port *port = ctx->info->port;
	s32 priority = ctx->data.s32_val;

	if (port->priority == priority)
		return 0;
	port->priority = priority;
	team_queue_override_port_prio_changed(team, port);
	return 0;
}