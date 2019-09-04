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
typedef  int /*<<< orphan*/  u32 ;
struct p_barrier_ack {int /*<<< orphan*/  set_size; int /*<<< orphan*/  barrier; } ;
struct drbd_socket {int dummy; } ;
struct drbd_connection {scalar_t__ cstate; struct drbd_socket meta; } ;

/* Variables and functions */
 scalar_t__ C_WF_REPORT_PARAMS ; 
 int /*<<< orphan*/  P_BARRIER_ACK ; 
 struct p_barrier_ack* conn_prepare_command (struct drbd_connection*,struct drbd_socket*) ; 
 int /*<<< orphan*/  conn_send_command (struct drbd_connection*,struct drbd_socket*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

void drbd_send_b_ack(struct drbd_connection *connection, u32 barrier_nr, u32 set_size)
{
	struct drbd_socket *sock;
	struct p_barrier_ack *p;

	if (connection->cstate < C_WF_REPORT_PARAMS)
		return;

	sock = &connection->meta;
	p = conn_prepare_command(connection, sock);
	if (!p)
		return;
	p->barrier = barrier_nr;
	p->set_size = cpu_to_be32(set_size);
	conn_send_command(connection, sock, P_BARRIER_ACK, sizeof(*p), NULL, 0);
}