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
struct socket {scalar_t__ type; int /*<<< orphan*/  state; int /*<<< orphan*/ * ops; } ;
struct sock {int sk_protocol; int /*<<< orphan*/  sk_state; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MISDN_OPEN ; 
 int /*<<< orphan*/  PF_ISDN ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 int /*<<< orphan*/  data_sock_ops ; 
 int /*<<< orphan*/  data_sockets ; 
 int /*<<< orphan*/  mISDN_proto ; 
 int /*<<< orphan*/  mISDN_sock_link (int /*<<< orphan*/ *,struct sock*) ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
data_sock_create(struct net *net, struct socket *sock, int protocol, int kern)
{
	struct sock *sk;

	if (sock->type != SOCK_DGRAM)
		return -ESOCKTNOSUPPORT;

	sk = sk_alloc(net, PF_ISDN, GFP_KERNEL, &mISDN_proto, kern);
	if (!sk)
		return -ENOMEM;

	sock_init_data(sock, sk);

	sock->ops = &data_sock_ops;
	sock->state = SS_UNCONNECTED;
	sock_reset_flag(sk, SOCK_ZAPPED);

	sk->sk_protocol = protocol;
	sk->sk_state    = MISDN_OPEN;
	mISDN_sock_link(&data_sockets, sk);

	return 0;
}