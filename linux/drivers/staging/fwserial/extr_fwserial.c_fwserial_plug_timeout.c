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
struct timer_list {int dummy; } ;
struct fwtty_port {int dummy; } ;
struct fwtty_peer {scalar_t__ state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ FWPS_PLUG_PENDING ; 
 struct fwtty_peer* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwserial_release_port (struct fwtty_port*,int) ; 
 struct fwtty_peer* peer ; 
 struct fwtty_port* peer_revert_state (struct fwtty_peer*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void fwserial_plug_timeout(struct timer_list *t)
{
	struct fwtty_peer *peer = from_timer(peer, t, timer);
	struct fwtty_port *port;

	spin_lock_bh(&peer->lock);
	if (peer->state != FWPS_PLUG_PENDING) {
		spin_unlock_bh(&peer->lock);
		return;
	}

	port = peer_revert_state(peer);
	spin_unlock_bh(&peer->lock);

	if (port)
		fwserial_release_port(port, false);
}