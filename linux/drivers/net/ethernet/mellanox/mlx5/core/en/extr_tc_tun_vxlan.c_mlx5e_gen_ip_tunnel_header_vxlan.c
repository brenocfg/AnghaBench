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
struct vxlanhdr {int /*<<< orphan*/  vx_vni; int /*<<< orphan*/  vx_flags; } ;
struct udphdr {int /*<<< orphan*/  dest; } ;
struct mlx5e_encap_entry {TYPE_1__* tun_info; } ;
struct ip_tunnel_key {int /*<<< orphan*/  tp_dst; int /*<<< orphan*/  tun_id; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct ip_tunnel_key key; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  VXLAN_HF_VNI ; 
 int /*<<< orphan*/  tunnel_id_to_key32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_vni_field (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_gen_ip_tunnel_header_vxlan(char buf[],
					    __u8 *ip_proto,
					    struct mlx5e_encap_entry *e)
{
	const struct ip_tunnel_key *tun_key = &e->tun_info->key;
	__be32 tun_id = tunnel_id_to_key32(tun_key->tun_id);
	struct udphdr *udp = (struct udphdr *)(buf);
	struct vxlanhdr *vxh;

	vxh = (struct vxlanhdr *)((char *)udp + sizeof(struct udphdr));
	*ip_proto = IPPROTO_UDP;

	udp->dest = tun_key->tp_dst;
	vxh->vx_flags = VXLAN_HF_VNI;
	vxh->vx_vni = vxlan_vni_field(tun_id);

	return 0;
}