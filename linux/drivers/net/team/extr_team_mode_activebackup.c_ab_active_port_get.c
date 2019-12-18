#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct team_port {TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  u32_val; } ;
struct team_gsetter_ctx {TYPE_2__ data; } ;
struct team {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  active_port; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 TYPE_3__* ab_priv (struct team*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct team_port* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab_active_port_get(struct team *team, struct team_gsetter_ctx *ctx)
{
	struct team_port *active_port;

	active_port = rcu_dereference_protected(ab_priv(team)->active_port,
						lockdep_is_held(&team->lock));
	if (active_port)
		ctx->data.u32_val = active_port->dev->ifindex;
	else
		ctx->data.u32_val = 0;
	return 0;
}