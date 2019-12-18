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
struct nfp_fl_push_vlan {int dummy; } ;
struct TYPE_2__ {int act_len; int /*<<< orphan*/  shortcut; } ;
struct nfp_fl_payload {char* action_data; TYPE_1__ meta; } ;
struct nfp_fl_output {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NFP_FL_MAX_A_SIZ ; 
 int /*<<< orphan*/  NFP_FL_SC_ACT_NULL ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 int nfp_fl_push_vlan_after_tun (char*,unsigned int,struct nfp_fl_push_vlan*) ; 
 int nfp_fl_verify_post_tun_acts (char*,unsigned int,struct nfp_fl_push_vlan**) ; 
 unsigned int nfp_flower_copy_pre_actions (char*,char*,unsigned int,int*) ; 

__attribute__((used)) static int
nfp_flower_merge_action(struct nfp_fl_payload *sub_flow1,
			struct nfp_fl_payload *sub_flow2,
			struct nfp_fl_payload *merge_flow)
{
	unsigned int sub1_act_len, sub2_act_len, pre_off1, pre_off2;
	struct nfp_fl_push_vlan *post_tun_push_vlan = NULL;
	bool tunnel_act = false;
	char *merge_act;
	int err;

	/* The last action of sub_flow1 must be output - do not merge this. */
	sub1_act_len = sub_flow1->meta.act_len - sizeof(struct nfp_fl_output);
	sub2_act_len = sub_flow2->meta.act_len;

	if (!sub2_act_len)
		return -EINVAL;

	if (sub1_act_len + sub2_act_len > NFP_FL_MAX_A_SIZ)
		return -EINVAL;

	/* A shortcut can only be applied if there is a single action. */
	if (sub1_act_len)
		merge_flow->meta.shortcut = cpu_to_be32(NFP_FL_SC_ACT_NULL);
	else
		merge_flow->meta.shortcut = sub_flow2->meta.shortcut;

	merge_flow->meta.act_len = sub1_act_len + sub2_act_len;
	merge_act = merge_flow->action_data;

	/* Copy any pre-actions to the start of merge flow action list. */
	pre_off1 = nfp_flower_copy_pre_actions(merge_act,
					       sub_flow1->action_data,
					       sub1_act_len, &tunnel_act);
	merge_act += pre_off1;
	sub1_act_len -= pre_off1;
	pre_off2 = nfp_flower_copy_pre_actions(merge_act,
					       sub_flow2->action_data,
					       sub2_act_len, NULL);
	merge_act += pre_off2;
	sub2_act_len -= pre_off2;

	/* FW does a tunnel push when egressing, therefore, if sub_flow 1 pushes
	 * a tunnel, there are restrictions on what sub_flow 2 actions lead to a
	 * valid merge.
	 */
	if (tunnel_act) {
		char *post_tun_acts = &sub_flow2->action_data[pre_off2];

		err = nfp_fl_verify_post_tun_acts(post_tun_acts, sub2_act_len,
						  &post_tun_push_vlan);
		if (err)
			return err;

		if (post_tun_push_vlan) {
			pre_off2 += sizeof(*post_tun_push_vlan);
			sub2_act_len -= sizeof(*post_tun_push_vlan);
		}
	}

	/* Copy remaining actions from sub_flows 1 and 2. */
	memcpy(merge_act, sub_flow1->action_data + pre_off1, sub1_act_len);

	if (post_tun_push_vlan) {
		/* Update tunnel action in merge to include VLAN push. */
		err = nfp_fl_push_vlan_after_tun(merge_act, sub1_act_len,
						 post_tun_push_vlan);
		if (err)
			return err;

		merge_flow->meta.act_len -= sizeof(*post_tun_push_vlan);
	}

	merge_act += sub1_act_len;
	memcpy(merge_act, sub_flow2->action_data + pre_off2, sub2_act_len);

	return 0;
}