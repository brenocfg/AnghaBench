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
typedef  int /*<<< orphan*/  tunnel_cfg ;
struct udp_tunnel_sock_cfg {int encap_type; int /*<<< orphan*/ * encap_destroy; int /*<<< orphan*/  encap_err_lookup; int /*<<< orphan*/  encap_rcv; int /*<<< orphan*/  gro_complete; int /*<<< orphan*/  gro_receive; struct geneve_sock* sk_user_data; } ;
struct socket {int dummy; } ;
struct net {int dummy; } ;
struct geneve_sock {int refcnt; int /*<<< orphan*/  list; struct socket* sock; int /*<<< orphan*/ * vni_list; } ;
struct geneve_net {int /*<<< orphan*/  sock_list; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct geneve_sock* ERR_CAST (struct socket*) ; 
 struct geneve_sock* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct socket*) ; 
 int /*<<< orphan*/  UDP_TUNNEL_TYPE_GENEVE ; 
 int VNI_HASH_SIZE ; 
 struct socket* geneve_create_sock (struct net*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  geneve_gro_complete ; 
 int /*<<< orphan*/  geneve_gro_receive ; 
 int /*<<< orphan*/  geneve_net_id ; 
 int /*<<< orphan*/  geneve_udp_encap_err_lookup ; 
 int /*<<< orphan*/  geneve_udp_encap_recv ; 
 int /*<<< orphan*/  kfree (struct geneve_sock*) ; 
 struct geneve_sock* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct udp_tunnel_sock_cfg*,int /*<<< orphan*/ ,int) ; 
 struct geneve_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_udp_tunnel_sock (struct net*,struct socket*,struct udp_tunnel_sock_cfg*) ; 
 int /*<<< orphan*/  udp_tunnel_notify_add_rx_port (struct socket*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct geneve_sock *geneve_socket_create(struct net *net, __be16 port,
						bool ipv6, bool ipv6_rx_csum)
{
	struct geneve_net *gn = net_generic(net, geneve_net_id);
	struct geneve_sock *gs;
	struct socket *sock;
	struct udp_tunnel_sock_cfg tunnel_cfg;
	int h;

	gs = kzalloc(sizeof(*gs), GFP_KERNEL);
	if (!gs)
		return ERR_PTR(-ENOMEM);

	sock = geneve_create_sock(net, ipv6, port, ipv6_rx_csum);
	if (IS_ERR(sock)) {
		kfree(gs);
		return ERR_CAST(sock);
	}

	gs->sock = sock;
	gs->refcnt = 1;
	for (h = 0; h < VNI_HASH_SIZE; ++h)
		INIT_HLIST_HEAD(&gs->vni_list[h]);

	/* Initialize the geneve udp offloads structure */
	udp_tunnel_notify_add_rx_port(gs->sock, UDP_TUNNEL_TYPE_GENEVE);

	/* Mark socket as an encapsulation socket */
	memset(&tunnel_cfg, 0, sizeof(tunnel_cfg));
	tunnel_cfg.sk_user_data = gs;
	tunnel_cfg.encap_type = 1;
	tunnel_cfg.gro_receive = geneve_gro_receive;
	tunnel_cfg.gro_complete = geneve_gro_complete;
	tunnel_cfg.encap_rcv = geneve_udp_encap_recv;
	tunnel_cfg.encap_err_lookup = geneve_udp_encap_err_lookup;
	tunnel_cfg.encap_destroy = NULL;
	setup_udp_tunnel_sock(net, sock, &tunnel_cfg);
	list_add(&gs->list, &gn->sock_list);
	return gs;
}