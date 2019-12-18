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
struct udp_tunnel_sock_cfg {int encap_type; int /*<<< orphan*/  encap_destroy; int /*<<< orphan*/  encap_rcv; struct gtp_dev* sk_user_data; int /*<<< orphan*/ * member_0; } ;
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_protocol; scalar_t__ sk_user_data; } ;
struct gtp_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 struct sock* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  gtp_encap_destroy ; 
 int /*<<< orphan*/  gtp_encap_recv ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  setup_udp_tunnel_sock (int /*<<< orphan*/ ,struct socket*,struct udp_tunnel_sock_cfg*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 struct socket* sockfd_lookup (int,int*) ; 
 int /*<<< orphan*/  sockfd_put (struct socket*) ; 

__attribute__((used)) static struct sock *gtp_encap_enable_socket(int fd, int type,
					    struct gtp_dev *gtp)
{
	struct udp_tunnel_sock_cfg tuncfg = {NULL};
	struct socket *sock;
	struct sock *sk;
	int err;

	pr_debug("enable gtp on %d, %d\n", fd, type);

	sock = sockfd_lookup(fd, &err);
	if (!sock) {
		pr_debug("gtp socket fd=%d not found\n", fd);
		return NULL;
	}

	if (sock->sk->sk_protocol != IPPROTO_UDP) {
		pr_debug("socket fd=%d not UDP\n", fd);
		sk = ERR_PTR(-EINVAL);
		goto out_sock;
	}

	lock_sock(sock->sk);
	if (sock->sk->sk_user_data) {
		sk = ERR_PTR(-EBUSY);
		goto out_sock;
	}

	sk = sock->sk;
	sock_hold(sk);

	tuncfg.sk_user_data = gtp;
	tuncfg.encap_type = type;
	tuncfg.encap_rcv = gtp_encap_recv;
	tuncfg.encap_destroy = gtp_encap_destroy;

	setup_udp_tunnel_sock(sock_net(sock->sk), sock, &tuncfg);

out_sock:
	release_sock(sock->sk);
	sockfd_put(sock);
	return sk;
}