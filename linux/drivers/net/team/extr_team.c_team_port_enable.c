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
struct team_port {scalar_t__ index; int /*<<< orphan*/  hlist; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* port_enabled ) (struct team*,struct team_port*) ;} ;
struct team {TYPE_1__ ops; int /*<<< orphan*/  en_port_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct team*,struct team_port*) ; 
 int /*<<< orphan*/  team_adjust_ops (struct team*) ; 
 int /*<<< orphan*/  team_lower_state_changed (struct team_port*) ; 
 int /*<<< orphan*/  team_mcast_rejoin (struct team*) ; 
 int /*<<< orphan*/  team_notify_peers (struct team*) ; 
 scalar_t__ team_port_enabled (struct team_port*) ; 
 int /*<<< orphan*/  team_port_index_hash (struct team*,scalar_t__) ; 
 int /*<<< orphan*/  team_queue_override_port_add (struct team*,struct team_port*) ; 

__attribute__((used)) static void team_port_enable(struct team *team,
			     struct team_port *port)
{
	if (team_port_enabled(port))
		return;
	port->index = team->en_port_count++;
	hlist_add_head_rcu(&port->hlist,
			   team_port_index_hash(team, port->index));
	team_adjust_ops(team);
	team_queue_override_port_add(team, port);
	if (team->ops.port_enabled)
		team->ops.port_enabled(team, port);
	team_notify_peers(team);
	team_mcast_rejoin(team);
	team_lower_state_changed(port);
}