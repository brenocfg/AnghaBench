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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5e_encap_entry {TYPE_1__* tun_info; } ;
struct ip_tunnel_key {int tun_flags; int /*<<< orphan*/  tun_id; } ;
struct gre_base_hdr {int /*<<< orphan*/  flags; int /*<<< orphan*/  protocol; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct ip_tunnel_key key; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_TEB ; 
 int /*<<< orphan*/  IPPROTO_GRE ; 
 int TUNNEL_CSUM ; 
 int TUNNEL_KEY ; 
 int TUNNEL_SEQ ; 
 int /*<<< orphan*/  gre_tnl_flags_to_gre_flags (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int mlx5e_tc_tun_calc_hlen_gretap (struct mlx5e_encap_entry*) ; 
 int /*<<< orphan*/  tunnel_id_to_key32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_gen_ip_tunnel_header_gretap(char buf[],
					     __u8 *ip_proto,
					     struct mlx5e_encap_entry *e)
{
	const struct ip_tunnel_key *tun_key  = &e->tun_info->key;
	struct gre_base_hdr *greh = (struct gre_base_hdr *)(buf);
	__be32 tun_id = tunnel_id_to_key32(tun_key->tun_id);
	int hdr_len;

	*ip_proto = IPPROTO_GRE;

	/* the HW does not calculate GRE csum or sequences */
	if (tun_key->tun_flags & (TUNNEL_CSUM | TUNNEL_SEQ))
		return -EOPNOTSUPP;

	greh->protocol = htons(ETH_P_TEB);

	/* GRE key */
	hdr_len	= mlx5e_tc_tun_calc_hlen_gretap(e);
	greh->flags = gre_tnl_flags_to_gre_flags(tun_key->tun_flags);
	if (tun_key->tun_flags & TUNNEL_KEY) {
		__be32 *ptr = (__be32 *)(((u8 *)greh) + hdr_len - 4);
		*ptr = tun_id;
	}

	return 0;
}