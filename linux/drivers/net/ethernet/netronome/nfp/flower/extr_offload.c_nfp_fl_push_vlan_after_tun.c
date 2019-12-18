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
struct nfp_fl_set_ipv4_tun {int /*<<< orphan*/  outer_vlan_tci; int /*<<< orphan*/  outer_vlan_tpid; } ;
struct nfp_fl_push_vlan {int /*<<< orphan*/  vlan_tci; int /*<<< orphan*/  vlan_tpid; } ;
struct nfp_fl_act_head {scalar_t__ jump_id; unsigned int len_lw; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ NFP_FL_ACTION_OPCODE_SET_IPV4_TUNNEL ; 
 unsigned int NFP_FL_LW_SIZ ; 

__attribute__((used)) static int
nfp_fl_push_vlan_after_tun(char *acts, int len, struct nfp_fl_push_vlan *vlan)
{
	struct nfp_fl_set_ipv4_tun *tun;
	struct nfp_fl_act_head *a;
	unsigned int act_off = 0;

	while (act_off < len) {
		a = (struct nfp_fl_act_head *)&acts[act_off];

		if (a->jump_id == NFP_FL_ACTION_OPCODE_SET_IPV4_TUNNEL) {
			tun = (struct nfp_fl_set_ipv4_tun *)a;
			tun->outer_vlan_tpid = vlan->vlan_tpid;
			tun->outer_vlan_tci = vlan->vlan_tci;

			return 0;
		}

		act_off += a->len_lw << NFP_FL_LW_SIZ;
	}

	/* Return error if no tunnel action is found. */
	return -EOPNOTSUPP;
}