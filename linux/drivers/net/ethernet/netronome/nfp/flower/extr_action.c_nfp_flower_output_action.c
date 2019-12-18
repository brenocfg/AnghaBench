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
typedef  scalar_t__ u32 ;
struct nfp_flower_priv {int flower_ext_feats; } ;
struct nfp_fl_payload {int /*<<< orphan*/ * action_data; } ;
struct nfp_fl_output {int dummy; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct flow_action_entry {int dummy; } ;
typedef  enum nfp_flower_tun_type { ____Placeholder_nfp_flower_tun_type } nfp_flower_tun_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int NFP_FL_FEATS_LAG ; 
 int NFP_FL_MAX_A_SIZ ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int nfp_fl_output (struct nfp_app*,struct nfp_fl_output*,struct flow_action_entry const*,struct nfp_fl_payload*,int,struct net_device*,int,int*,int,struct netlink_ext_ack*) ; 
 int nfp_fl_pre_lag (struct nfp_app*,struct flow_action_entry const*,struct nfp_fl_payload*,int,struct netlink_ext_ack*) ; 

__attribute__((used)) static int
nfp_flower_output_action(struct nfp_app *app,
			 const struct flow_action_entry *act,
			 struct nfp_fl_payload *nfp_fl, int *a_len,
			 struct net_device *netdev, bool last,
			 enum nfp_flower_tun_type *tun_type, int *tun_out_cnt,
			 int *out_cnt, u32 *csum_updated, bool pkt_host,
			 struct netlink_ext_ack *extack)
{
	struct nfp_flower_priv *priv = app->priv;
	struct nfp_fl_output *output;
	int err, prelag_size;

	/* If csum_updated has not been reset by now, it means HW will
	 * incorrectly update csums when they are not requested.
	 */
	if (*csum_updated) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: set actions without updating checksums are not supported");
		return -EOPNOTSUPP;
	}

	if (*a_len + sizeof(struct nfp_fl_output) > NFP_FL_MAX_A_SIZ) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: mirred output increases action list size beyond the allowed maximum");
		return -EOPNOTSUPP;
	}

	output = (struct nfp_fl_output *)&nfp_fl->action_data[*a_len];
	err = nfp_fl_output(app, output, act, nfp_fl, last, netdev, *tun_type,
			    tun_out_cnt, pkt_host, extack);
	if (err)
		return err;

	*a_len += sizeof(struct nfp_fl_output);

	if (priv->flower_ext_feats & NFP_FL_FEATS_LAG) {
		/* nfp_fl_pre_lag returns -err or size of prelag action added.
		 * This will be 0 if it is not egressing to a lag dev.
		 */
		prelag_size = nfp_fl_pre_lag(app, act, nfp_fl, *a_len, extack);
		if (prelag_size < 0) {
			return prelag_size;
		} else if (prelag_size > 0 && (!last || *out_cnt)) {
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: LAG action has to be last action in action list");
			return -EOPNOTSUPP;
		}

		*a_len += prelag_size;
	}
	(*out_cnt)++;

	return 0;
}