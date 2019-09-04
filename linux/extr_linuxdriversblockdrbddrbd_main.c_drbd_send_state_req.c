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
union drbd_state {int /*<<< orphan*/  i; } ;
struct p_req_state {void* val; void* mask; } ;
struct drbd_socket {int dummy; } ;
struct drbd_peer_device {TYPE_1__* connection; } ;
struct TYPE_2__ {struct drbd_socket data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  P_STATE_CHG_REQ ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct p_req_state* drbd_prepare_command (struct drbd_peer_device*,struct drbd_socket*) ; 
 int drbd_send_command (struct drbd_peer_device*,struct drbd_socket*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int drbd_send_state_req(struct drbd_peer_device *peer_device, union drbd_state mask, union drbd_state val)
{
	struct drbd_socket *sock;
	struct p_req_state *p;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	if (!p)
		return -EIO;
	p->mask = cpu_to_be32(mask.i);
	p->val = cpu_to_be32(val.i);
	return drbd_send_command(peer_device, sock, P_STATE_CHG_REQ, sizeof(*p), NULL, 0);
}