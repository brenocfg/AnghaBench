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
struct socket {int /*<<< orphan*/ * ops; int /*<<< orphan*/  state; } ;
struct sock {int /*<<< orphan*/  sk_destruct; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_family; int /*<<< orphan*/  sk_type; int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_backlog_rcv; } ;
struct pptp_opt {int seq_recv; int ack_sent; scalar_t__ ack_recv; scalar_t__ seq_sent; } ;
struct TYPE_2__ {struct pptp_opt pptp; } ;
struct pppox_sock {TYPE_1__ proto; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PF_PPPOX ; 
 int /*<<< orphan*/  PPPOX_NONE ; 
 int /*<<< orphan*/  PX_PROTO_PPTP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 struct pppox_sock* pppox_sk (struct sock*) ; 
 int /*<<< orphan*/  pptp_ops ; 
 int /*<<< orphan*/  pptp_rcv_core ; 
 int /*<<< orphan*/  pptp_sk_proto ; 
 int /*<<< orphan*/  pptp_sock_destruct ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 

__attribute__((used)) static int pptp_create(struct net *net, struct socket *sock, int kern)
{
	int error = -ENOMEM;
	struct sock *sk;
	struct pppox_sock *po;
	struct pptp_opt *opt;

	sk = sk_alloc(net, PF_PPPOX, GFP_KERNEL, &pptp_sk_proto, kern);
	if (!sk)
		goto out;

	sock_init_data(sock, sk);

	sock->state = SS_UNCONNECTED;
	sock->ops   = &pptp_ops;

	sk->sk_backlog_rcv = pptp_rcv_core;
	sk->sk_state       = PPPOX_NONE;
	sk->sk_type        = SOCK_STREAM;
	sk->sk_family      = PF_PPPOX;
	sk->sk_protocol    = PX_PROTO_PPTP;
	sk->sk_destruct    = pptp_sock_destruct;

	po = pppox_sk(sk);
	opt = &po->proto.pptp;

	opt->seq_sent = 0; opt->seq_recv = 0xffffffff;
	opt->ack_recv = 0; opt->ack_sent = 0xffffffff;

	error = 0;
out:
	return error;
}