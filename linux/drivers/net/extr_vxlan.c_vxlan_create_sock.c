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
typedef  int /*<<< orphan*/  udp_conf ;
typedef  int u32 ;
struct udp_port_cfg {int use_udp6_rx_checksums; int ipv6_v6only; int bind_ifindex; int /*<<< orphan*/  local_udp_port; int /*<<< orphan*/  family; } ;
struct socket {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 struct socket* ERR_PTR (int) ; 
 int VXLAN_F_UDP_ZERO_CSUM6_RX ; 
 int /*<<< orphan*/  memset (struct udp_port_cfg*,int /*<<< orphan*/ ,int) ; 
 int udp_sock_create (struct net*,struct udp_port_cfg*,struct socket**) ; 

__attribute__((used)) static struct socket *vxlan_create_sock(struct net *net, bool ipv6,
					__be16 port, u32 flags, int ifindex)
{
	struct socket *sock;
	struct udp_port_cfg udp_conf;
	int err;

	memset(&udp_conf, 0, sizeof(udp_conf));

	if (ipv6) {
		udp_conf.family = AF_INET6;
		udp_conf.use_udp6_rx_checksums =
		    !(flags & VXLAN_F_UDP_ZERO_CSUM6_RX);
		udp_conf.ipv6_v6only = 1;
	} else {
		udp_conf.family = AF_INET;
	}

	udp_conf.local_udp_port = port;
	udp_conf.bind_ifindex = ifindex;

	/* Open UDP socket */
	err = udp_sock_create(net, &udp_conf, &sock);
	if (err < 0)
		return ERR_PTR(err);

	return sock;
}