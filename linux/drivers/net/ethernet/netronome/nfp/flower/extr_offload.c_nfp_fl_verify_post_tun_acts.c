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
struct nfp_fl_push_vlan {int dummy; } ;
struct nfp_fl_act_head {scalar_t__ jump_id; unsigned int len_lw; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ NFP_FL_ACTION_OPCODE_OUTPUT ; 
 scalar_t__ NFP_FL_ACTION_OPCODE_PUSH_VLAN ; 
 unsigned int NFP_FL_LW_SIZ ; 

__attribute__((used)) static int
nfp_fl_verify_post_tun_acts(char *acts, int len, struct nfp_fl_push_vlan **vlan)
{
	struct nfp_fl_act_head *a;
	unsigned int act_off = 0;

	while (act_off < len) {
		a = (struct nfp_fl_act_head *)&acts[act_off];

		if (a->jump_id == NFP_FL_ACTION_OPCODE_PUSH_VLAN && !act_off)
			*vlan = (struct nfp_fl_push_vlan *)a;
		else if (a->jump_id != NFP_FL_ACTION_OPCODE_OUTPUT)
			return -EOPNOTSUPP;

		act_off += a->len_lw << NFP_FL_LW_SIZ;
	}

	/* Ensure any VLAN push also has an egress action. */
	if (*vlan && act_off <= sizeof(struct nfp_fl_push_vlan))
		return -EOPNOTSUPP;

	return 0;
}