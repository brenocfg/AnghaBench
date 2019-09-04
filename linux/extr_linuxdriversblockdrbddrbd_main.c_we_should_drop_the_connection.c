#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  task; } ;
struct TYPE_4__ {struct socket* socket; } ;
struct drbd_connection {scalar_t__ cstate; int /*<<< orphan*/  ko_count; TYPE_2__ ack_receiver; TYPE_1__ meta; } ;
struct TYPE_6__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 scalar_t__ C_WF_REPORT_PARAMS ; 
 scalar_t__ RUNNING ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  drbd_err (struct drbd_connection*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_t_state (TYPE_2__*) ; 
 int /*<<< orphan*/  request_ping (struct drbd_connection*) ; 

__attribute__((used)) static int we_should_drop_the_connection(struct drbd_connection *connection, struct socket *sock)
{
	int drop_it;
	/* long elapsed = (long)(jiffies - device->last_received); */

	drop_it =   connection->meta.socket == sock
		|| !connection->ack_receiver.task
		|| get_t_state(&connection->ack_receiver) != RUNNING
		|| connection->cstate < C_WF_REPORT_PARAMS;

	if (drop_it)
		return true;

	drop_it = !--connection->ko_count;
	if (!drop_it) {
		drbd_err(connection, "[%s/%d] sock_sendmsg time expired, ko = %u\n",
			 current->comm, current->pid, connection->ko_count);
		request_ping(connection);
	}

	return drop_it; /* && (device->state == R_PRIMARY) */;
}