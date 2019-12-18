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
struct fwtty_port {int /*<<< orphan*/  peer; } ;
struct fwtty_peer {int /*<<< orphan*/  status_addr; } ;
typedef  int /*<<< orphan*/  status ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 unsigned int __fwtty_port_line_status (struct fwtty_port*) ; 
 int fwtty_send_data_async (struct fwtty_peer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int,int /*<<< orphan*/ *,struct fwtty_port*) ; 
 struct fwtty_peer* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int __fwtty_write_port_status(struct fwtty_port *port)
{
	struct fwtty_peer *peer;
	int err = -ENOENT;
	unsigned int status = __fwtty_port_line_status(port);

	rcu_read_lock();
	peer = rcu_dereference(port->peer);
	if (peer) {
		err = fwtty_send_data_async(peer, TCODE_WRITE_QUADLET_REQUEST,
					    peer->status_addr, &status,
					    sizeof(status), NULL, port);
	}
	rcu_read_unlock();

	return err;
}