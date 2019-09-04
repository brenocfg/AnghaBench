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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct nfp_repr {TYPE_1__* app; } ;
struct nfp_fl_rule_metadata {int dummy; } ;
struct TYPE_4__ {size_t key_len; size_t mask_len; size_t act_len; } ;
struct nfp_fl_payload {TYPE_2__ meta; TYPE_2__* action_data; TYPE_2__* mask_data; TYPE_2__* unmasked_data; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NFP_FL_LW_SIZ ; 
 int /*<<< orphan*/  memcpy (unsigned char*,TYPE_2__*,size_t) ; 
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nfp_ctrl_tx (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* nfp_flower_cmsg_alloc (TYPE_1__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char* nfp_flower_cmsg_get_data (struct sk_buff*) ; 

__attribute__((used)) static int
nfp_flower_xmit_flow(struct net_device *netdev,
		     struct nfp_fl_payload *nfp_flow, u8 mtype)
{
	u32 meta_len, key_len, mask_len, act_len, tot_len;
	struct nfp_repr *priv = netdev_priv(netdev);
	struct sk_buff *skb;
	unsigned char *msg;

	meta_len =  sizeof(struct nfp_fl_rule_metadata);
	key_len = nfp_flow->meta.key_len;
	mask_len = nfp_flow->meta.mask_len;
	act_len = nfp_flow->meta.act_len;

	tot_len = meta_len + key_len + mask_len + act_len;

	/* Convert to long words as firmware expects
	 * lengths in units of NFP_FL_LW_SIZ.
	 */
	nfp_flow->meta.key_len >>= NFP_FL_LW_SIZ;
	nfp_flow->meta.mask_len >>= NFP_FL_LW_SIZ;
	nfp_flow->meta.act_len >>= NFP_FL_LW_SIZ;

	skb = nfp_flower_cmsg_alloc(priv->app, tot_len, mtype, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	msg = nfp_flower_cmsg_get_data(skb);
	memcpy(msg, &nfp_flow->meta, meta_len);
	memcpy(&msg[meta_len], nfp_flow->unmasked_data, key_len);
	memcpy(&msg[meta_len + key_len], nfp_flow->mask_data, mask_len);
	memcpy(&msg[meta_len + key_len + mask_len],
	       nfp_flow->action_data, act_len);

	/* Convert back to bytes as software expects
	 * lengths in units of bytes.
	 */
	nfp_flow->meta.key_len <<= NFP_FL_LW_SIZ;
	nfp_flow->meta.mask_len <<= NFP_FL_LW_SIZ;
	nfp_flow->meta.act_len <<= NFP_FL_LW_SIZ;

	nfp_ctrl_tx(priv->app->ctrl, skb);

	return 0;
}