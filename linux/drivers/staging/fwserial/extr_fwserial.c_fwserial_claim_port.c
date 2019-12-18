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
struct fwtty_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  peer; } ;
struct fwtty_peer {TYPE_1__* serial; } ;
struct TYPE_2__ {struct fwtty_port** ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 struct fwtty_port* ERR_PTR (int /*<<< orphan*/ ) ; 
 int num_ports ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct fwtty_peer*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static struct fwtty_port *fwserial_claim_port(struct fwtty_peer *peer,
					      int index)
{
	struct fwtty_port *port;

	if (index < 0 || index >= num_ports)
		return ERR_PTR(-EINVAL);

	/* must guarantee that previous port releases have completed */
	synchronize_rcu();

	port = peer->serial->ports[index];
	spin_lock_bh(&port->lock);
	if (!rcu_access_pointer(port->peer))
		rcu_assign_pointer(port->peer, peer);
	else
		port = ERR_PTR(-EBUSY);
	spin_unlock_bh(&port->lock);

	return port;
}