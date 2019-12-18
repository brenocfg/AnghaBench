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
struct TYPE_2__ {int tun_flags; int /*<<< orphan*/  tun_id; } ;
struct ip_tunnel_info {int options_len; TYPE_1__ key; } ;
struct genevehdr {int opt_len; int oam; int critical; int /*<<< orphan*/  options; scalar_t__ rsvd2; int /*<<< orphan*/  proto_type; int /*<<< orphan*/  vni; scalar_t__ rsvd1; int /*<<< orphan*/  ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_TEB ; 
 int /*<<< orphan*/  GENEVE_VER ; 
 int TUNNEL_CRIT_OPT ; 
 int TUNNEL_GENEVE_OPT ; 
 int TUNNEL_OAM ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_tunnel_info_opts_get (int /*<<< orphan*/ ,struct ip_tunnel_info const*) ; 
 int /*<<< orphan*/  tunnel_id_to_vni (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void geneve_build_header(struct genevehdr *geneveh,
				const struct ip_tunnel_info *info)
{
	geneveh->ver = GENEVE_VER;
	geneveh->opt_len = info->options_len / 4;
	geneveh->oam = !!(info->key.tun_flags & TUNNEL_OAM);
	geneveh->critical = !!(info->key.tun_flags & TUNNEL_CRIT_OPT);
	geneveh->rsvd1 = 0;
	tunnel_id_to_vni(info->key.tun_id, geneveh->vni);
	geneveh->proto_type = htons(ETH_P_TEB);
	geneveh->rsvd2 = 0;

	if (info->key.tun_flags & TUNNEL_GENEVE_OPT)
		ip_tunnel_info_opts_get(geneveh->options, info);
}