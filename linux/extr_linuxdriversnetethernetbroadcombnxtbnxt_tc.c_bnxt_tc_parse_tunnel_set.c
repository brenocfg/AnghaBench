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
struct tc_action {int dummy; } ;
struct ip_tunnel_key {int dummy; } ;
struct ip_tunnel_info {struct ip_tunnel_key key; } ;
struct bnxt_tc_actions {int /*<<< orphan*/  flags; struct ip_tunnel_key tun_encap_key; } ;
struct bnxt {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  BNXT_TC_ACTION_FLAG_TUNNEL_ENCAP ; 
 int EOPNOTSUPP ; 
 scalar_t__ ip_tunnel_info_af (struct ip_tunnel_info*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 struct ip_tunnel_info* tcf_tunnel_info (struct tc_action const*) ; 

__attribute__((used)) static int bnxt_tc_parse_tunnel_set(struct bnxt *bp,
				    struct bnxt_tc_actions *actions,
				    const struct tc_action *tc_act)
{
	struct ip_tunnel_info *tun_info = tcf_tunnel_info(tc_act);
	struct ip_tunnel_key *tun_key = &tun_info->key;

	if (ip_tunnel_info_af(tun_info) != AF_INET) {
		netdev_info(bp->dev, "only IPv4 tunnel-encap is supported");
		return -EOPNOTSUPP;
	}

	actions->tun_encap_key = *tun_key;
	actions->flags |= BNXT_TC_ACTION_FLAG_TUNNEL_ENCAP;
	return 0;
}