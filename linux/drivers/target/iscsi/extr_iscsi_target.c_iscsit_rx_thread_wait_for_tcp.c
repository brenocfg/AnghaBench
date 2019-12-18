#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iscsi_conn {int /*<<< orphan*/  rx_half_close_comp; TYPE_2__* sock; } ;
struct TYPE_4__ {TYPE_1__* sk; } ;
struct TYPE_3__ {int sk_shutdown; } ;

/* Variables and functions */
 int HZ ; 
 int ISCSI_RX_THREAD_TCP_TIMEOUT ; 
 int RCV_SHUTDOWN ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void iscsit_rx_thread_wait_for_tcp(struct iscsi_conn *conn)
{
	if ((conn->sock->sk->sk_shutdown & SEND_SHUTDOWN) ||
	    (conn->sock->sk->sk_shutdown & RCV_SHUTDOWN)) {
		wait_for_completion_interruptible_timeout(
					&conn->rx_half_close_comp,
					ISCSI_RX_THREAD_TCP_TIMEOUT * HZ);
	}
}