#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_8__ {struct stmmac_test_priv* af_packet_priv; TYPE_2__* dev; int /*<<< orphan*/  func; void* type; } ;
struct stmmac_test_priv {int ok; int double_vlan; int vlan_id; TYPE_4__ pt; int /*<<< orphan*/  comp; struct stmmac_packet_attrs* packet; } ;
struct TYPE_6__ {int /*<<< orphan*/  vlins; } ;
struct stmmac_priv {TYPE_2__* dev; TYPE_1__ dma_cap; } ;
struct stmmac_packet_attrs {int /*<<< orphan*/  dst; } ;
struct sk_buff {void* protocol; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_8021AD ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STMMAC_LB_TIMEOUT ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,void*,int) ; 
 int /*<<< orphan*/  dev_add_pack (TYPE_4__*) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_remove_pack (TYPE_4__*) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct stmmac_test_priv*) ; 
 struct stmmac_test_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* stmmac_test_get_udp_skb (struct stmmac_priv*,struct stmmac_packet_attrs*) ; 
 int /*<<< orphan*/  stmmac_test_vlan_validate ; 
 int vlan_vid_add (TYPE_2__*,void*,int) ; 
 int /*<<< orphan*/  vlan_vid_del (TYPE_2__*,void*,int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmmac_test_vlanoff_common(struct stmmac_priv *priv, bool svlan)
{
	struct stmmac_packet_attrs attr = { };
	struct stmmac_test_priv *tpriv;
	struct sk_buff *skb = NULL;
	int ret = 0;
	u16 proto;

	if (!priv->dma_cap.vlins)
		return -EOPNOTSUPP;

	tpriv = kzalloc(sizeof(*tpriv), GFP_KERNEL);
	if (!tpriv)
		return -ENOMEM;

	proto = svlan ? ETH_P_8021AD : ETH_P_8021Q;

	tpriv->ok = false;
	tpriv->double_vlan = svlan;
	init_completion(&tpriv->comp);

	tpriv->pt.type = svlan ? htons(ETH_P_8021Q) : htons(ETH_P_IP);
	tpriv->pt.func = stmmac_test_vlan_validate;
	tpriv->pt.dev = priv->dev;
	tpriv->pt.af_packet_priv = tpriv;
	tpriv->packet = &attr;
	tpriv->vlan_id = 0x123;
	dev_add_pack(&tpriv->pt);

	ret = vlan_vid_add(priv->dev, htons(proto), tpriv->vlan_id);
	if (ret)
		goto cleanup;

	attr.dst = priv->dev->dev_addr;

	skb = stmmac_test_get_udp_skb(priv, &attr);
	if (!skb) {
		ret = -ENOMEM;
		goto vlan_del;
	}

	__vlan_hwaccel_put_tag(skb, htons(proto), tpriv->vlan_id);
	skb->protocol = htons(proto);

	skb_set_queue_mapping(skb, 0);
	ret = dev_queue_xmit(skb);
	if (ret)
		goto vlan_del;

	wait_for_completion_timeout(&tpriv->comp, STMMAC_LB_TIMEOUT);
	ret = tpriv->ok ? 0 : -ETIMEDOUT;

vlan_del:
	vlan_vid_del(priv->dev, htons(proto), tpriv->vlan_id);
cleanup:
	dev_remove_pack(&tpriv->pt);
	kfree(tpriv);
	return ret;
}