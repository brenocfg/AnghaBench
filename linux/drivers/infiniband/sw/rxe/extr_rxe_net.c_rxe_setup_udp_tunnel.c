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
struct udp_tunnel_sock_cfg {int encap_type; int /*<<< orphan*/  encap_rcv; } ;
struct udp_port_cfg {int ipv6_v6only; int /*<<< orphan*/  local_udp_port; int /*<<< orphan*/  family; } ;
struct socket {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 struct socket* ERR_PTR (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rxe_udp_encap_recv ; 
 int /*<<< orphan*/  setup_udp_tunnel_sock (struct net*,struct socket*,struct udp_tunnel_sock_cfg*) ; 
 int udp_sock_create (struct net*,struct udp_port_cfg*,struct socket**) ; 

__attribute__((used)) static struct socket *rxe_setup_udp_tunnel(struct net *net, __be16 port,
					   bool ipv6)
{
	int err;
	struct socket *sock;
	struct udp_port_cfg udp_cfg = { };
	struct udp_tunnel_sock_cfg tnl_cfg = { };

	if (ipv6) {
		udp_cfg.family = AF_INET6;
		udp_cfg.ipv6_v6only = 1;
	} else {
		udp_cfg.family = AF_INET;
	}

	udp_cfg.local_udp_port = port;

	/* Create UDP socket */
	err = udp_sock_create(net, &udp_cfg, &sock);
	if (err < 0) {
		pr_err("failed to create udp socket. err = %d\n", err);
		return ERR_PTR(err);
	}

	tnl_cfg.encap_type = 1;
	tnl_cfg.encap_rcv = rxe_udp_encap_recv;

	/* Setup UDP tunnel */
	setup_udp_tunnel_sock(net, sock, &tnl_cfg);

	return sock;
}