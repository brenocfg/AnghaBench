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
struct team_port {int /*<<< orphan*/  qom_list; int /*<<< orphan*/  queue_id; } ;
struct team {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __team_queue_override_port_del(struct team *team,
					   struct team_port *port)
{
	if (!port->queue_id)
		return;
	list_del_rcu(&port->qom_list);
}