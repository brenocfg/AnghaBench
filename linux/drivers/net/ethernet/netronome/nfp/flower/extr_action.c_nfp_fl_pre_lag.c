#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t len_lw; int /*<<< orphan*/  jump_id; } ;
struct nfp_fl_pre_lag {TYPE_1__ head; } ;
struct TYPE_4__ {int /*<<< orphan*/  shortcut; } ;
struct nfp_fl_payload {TYPE_2__ meta; scalar_t__ action_data; } ;
struct nfp_app {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct flow_action_entry {struct net_device* dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NFP_FL_ACTION_OPCODE_PRE_LAG ; 
 size_t NFP_FL_LW_SIZ ; 
 int NFP_FL_MAX_A_SIZ ; 
 int /*<<< orphan*/  NFP_FL_SC_ACT_NULL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  netif_is_lag_master (struct net_device*) ; 
 int nfp_flower_lag_populate_pre_action (struct nfp_app*,struct net_device*,struct nfp_fl_pre_lag*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int
nfp_fl_pre_lag(struct nfp_app *app, const struct flow_action_entry *act,
	       struct nfp_fl_payload *nfp_flow, int act_len,
	       struct netlink_ext_ack *extack)
{
	size_t act_size = sizeof(struct nfp_fl_pre_lag);
	struct nfp_fl_pre_lag *pre_lag;
	struct net_device *out_dev;
	int err;

	out_dev = act->dev;
	if (!out_dev || !netif_is_lag_master(out_dev))
		return 0;

	if (act_len + act_size > NFP_FL_MAX_A_SIZ) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: maximum allowed action list size exceeded at LAG action");
		return -EOPNOTSUPP;
	}

	/* Pre_lag action must be first on action list.
	 * If other actions already exist they need pushed forward.
	 */
	if (act_len)
		memmove(nfp_flow->action_data + act_size,
			nfp_flow->action_data, act_len);

	pre_lag = (struct nfp_fl_pre_lag *)nfp_flow->action_data;
	err = nfp_flower_lag_populate_pre_action(app, out_dev, pre_lag, extack);
	if (err)
		return err;

	pre_lag->head.jump_id = NFP_FL_ACTION_OPCODE_PRE_LAG;
	pre_lag->head.len_lw = act_size >> NFP_FL_LW_SIZ;

	nfp_flow->meta.shortcut = cpu_to_be32(NFP_FL_SC_ACT_NULL);

	return act_size;
}