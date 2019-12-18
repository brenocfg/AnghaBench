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
struct team_port {int /*<<< orphan*/  queue_id; } ;
struct team {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __team_queue_override_enabled_check (struct team*) ; 
 int /*<<< orphan*/  __team_queue_override_port_add (struct team*,struct team_port*) ; 
 int /*<<< orphan*/  __team_queue_override_port_del (struct team*,struct team_port*) ; 
 scalar_t__ team_port_enabled (struct team_port*) ; 

__attribute__((used)) static void team_queue_override_port_prio_changed(struct team *team,
						  struct team_port *port)
{
	if (!port->queue_id || team_port_enabled(port))
		return;
	__team_queue_override_port_del(team, port);
	__team_queue_override_port_add(team, port);
	__team_queue_override_enabled_check(team);
}