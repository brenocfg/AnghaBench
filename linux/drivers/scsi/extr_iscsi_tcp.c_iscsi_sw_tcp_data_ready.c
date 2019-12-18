#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_callback_lock; struct iscsi_conn* sk_user_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  segment; } ;
struct iscsi_tcp_conn {TYPE_2__ in; } ;
struct iscsi_conn {struct iscsi_tcp_conn* dd_data; } ;
struct TYPE_5__ {struct iscsi_conn* data; } ;
struct TYPE_7__ {int count; TYPE_1__ arg; } ;
typedef  TYPE_3__ read_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_sw_sk_state_check (struct sock*) ; 
 int /*<<< orphan*/  iscsi_sw_tcp_recv ; 
 int /*<<< orphan*/  iscsi_tcp_segment_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_read_sock (struct sock*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iscsi_sw_tcp_data_ready(struct sock *sk)
{
	struct iscsi_conn *conn;
	struct iscsi_tcp_conn *tcp_conn;
	read_descriptor_t rd_desc;

	read_lock_bh(&sk->sk_callback_lock);
	conn = sk->sk_user_data;
	if (!conn) {
		read_unlock_bh(&sk->sk_callback_lock);
		return;
	}
	tcp_conn = conn->dd_data;

	/*
	 * Use rd_desc to pass 'conn' to iscsi_tcp_recv.
	 * We set count to 1 because we want the network layer to
	 * hand us all the skbs that are available. iscsi_tcp_recv
	 * handled pdus that cross buffers or pdus that still need data.
	 */
	rd_desc.arg.data = conn;
	rd_desc.count = 1;
	tcp_read_sock(sk, &rd_desc, iscsi_sw_tcp_recv);

	iscsi_sw_sk_state_check(sk);

	/* If we had to (atomically) map a highmem page,
	 * unmap it now. */
	iscsi_tcp_segment_unmap(&tcp_conn->in.segment);
	read_unlock_bh(&sk->sk_callback_lock);
}