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
struct mcast_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  table; } ;
struct mcast_group {int /*<<< orphan*/  node; int /*<<< orphan*/  refcount; struct mcast_port* port; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deref_port (struct mcast_port*) ; 
 int /*<<< orphan*/  kfree (struct mcast_group*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void release_group(struct mcast_group *group)
{
	struct mcast_port *port = group->port;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	if (atomic_dec_and_test(&group->refcount)) {
		rb_erase(&group->node, &port->table);
		spin_unlock_irqrestore(&port->lock, flags);
		kfree(group);
		deref_port(port);
	} else
		spin_unlock_irqrestore(&port->lock, flags);
}