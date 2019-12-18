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
struct fwtty_port {int dummy; } ;
struct fwtty_peer {int /*<<< orphan*/  lock; scalar_t__ guid; int /*<<< orphan*/  unit; int /*<<< orphan*/  list; struct fwtty_port* port; int /*<<< orphan*/  timer; TYPE_1__* serial; int /*<<< orphan*/  work; int /*<<< orphan*/  connect; } ;
struct TYPE_2__ {struct fwtty_peer* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWPS_GONE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwserial_release_port (struct fwtty_port*,int) ; 
 int /*<<< orphan*/  fwtty_info (int /*<<< orphan*/ *,char*,unsigned long long) ; 
 int /*<<< orphan*/  kfree (struct fwtty_peer*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  peer_set_state (struct fwtty_peer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void fwserial_remove_peer(struct fwtty_peer *peer)
{
	struct fwtty_port *port;

	spin_lock_bh(&peer->lock);
	peer_set_state(peer, FWPS_GONE);
	spin_unlock_bh(&peer->lock);

	cancel_delayed_work_sync(&peer->connect);
	cancel_work_sync(&peer->work);

	spin_lock_bh(&peer->lock);
	/* if this unit is the local unit, clear link */
	if (peer == peer->serial->self)
		peer->serial->self = NULL;

	/* cancel the request timeout timer (if running) */
	del_timer(&peer->timer);

	port = peer->port;
	peer->port = NULL;

	list_del_rcu(&peer->list);

	fwtty_info(&peer->unit, "peer removed (guid:%016llx)\n",
		   (unsigned long long)peer->guid);

	spin_unlock_bh(&peer->lock);

	if (port)
		fwserial_release_port(port, true);

	synchronize_rcu();
	kfree(peer);
}