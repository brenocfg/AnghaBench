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
 int num_ttys ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct fwtty_peer*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static struct fwtty_port *fwserial_find_port(struct fwtty_peer *peer)
{
	struct fwtty_port **ports = peer->serial->ports;
	int i;

	/* must guarantee that previous port releases have completed */
	synchronize_rcu();

	/* TODO: implement optional GUID-to-specific port # matching */

	/* find an unattached port (but not the loopback port, if present) */
	for (i = 0; i < num_ttys; ++i) {
		spin_lock_bh(&ports[i]->lock);
		if (!ports[i]->peer) {
			/* claim port */
			rcu_assign_pointer(ports[i]->peer, peer);
			spin_unlock_bh(&ports[i]->lock);
			return ports[i];
		}
		spin_unlock_bh(&ports[i]->lock);
	}
	return NULL;
}