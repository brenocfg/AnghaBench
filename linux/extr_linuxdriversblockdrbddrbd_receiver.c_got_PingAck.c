#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct packet_info {int dummy; } ;
struct TYPE_7__ {TYPE_2__* socket; } ;
struct drbd_connection {int /*<<< orphan*/  ping_wait; int /*<<< orphan*/  flags; TYPE_4__* net_conf; TYPE_3__ meta; } ;
struct TYPE_8__ {int ping_int; } ;
struct TYPE_6__ {TYPE_1__* sk; } ;
struct TYPE_5__ {int sk_rcvtimeo; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOT_PING_ACK ; 
 int HZ ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int got_PingAck(struct drbd_connection *connection, struct packet_info *pi)
{
	/* restore idle timeout */
	connection->meta.socket->sk->sk_rcvtimeo = connection->net_conf->ping_int*HZ;
	if (!test_and_set_bit(GOT_PING_ACK, &connection->flags))
		wake_up(&connection->ping_wait);

	return 0;
}