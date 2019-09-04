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
struct p_req_state_reply {int /*<<< orphan*/  retcode; } ;
struct drbd_socket {int dummy; } ;
struct drbd_peer_device {TYPE_1__* connection; } ;
typedef  enum drbd_state_rv { ____Placeholder_drbd_state_rv } drbd_state_rv ;
struct TYPE_2__ {struct drbd_socket meta; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_STATE_CHG_REPLY ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct p_req_state_reply* drbd_prepare_command (struct drbd_peer_device*,struct drbd_socket*) ; 
 int /*<<< orphan*/  drbd_send_command (struct drbd_peer_device*,struct drbd_socket*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void drbd_send_sr_reply(struct drbd_peer_device *peer_device, enum drbd_state_rv retcode)
{
	struct drbd_socket *sock;
	struct p_req_state_reply *p;

	sock = &peer_device->connection->meta;
	p = drbd_prepare_command(peer_device, sock);
	if (p) {
		p->retcode = cpu_to_be32(retcode);
		drbd_send_command(peer_device, sock, P_STATE_CHG_REPLY, sizeof(*p), NULL, 0);
	}
}