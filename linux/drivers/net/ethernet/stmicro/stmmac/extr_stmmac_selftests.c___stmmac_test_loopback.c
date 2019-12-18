#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct stmmac_test_priv* af_packet_priv; int /*<<< orphan*/  dev; int /*<<< orphan*/  func; int /*<<< orphan*/  type; } ;
struct stmmac_test_priv {int ok; TYPE_1__ pt; int /*<<< orphan*/  comp; struct stmmac_packet_attrs* packet; } ;
struct stmmac_priv {int /*<<< orphan*/  dev; } ;
struct stmmac_packet_attrs {scalar_t__ dont_wait; int /*<<< orphan*/  timeout; int /*<<< orphan*/  queue_mapping; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STMMAC_LB_TIMEOUT ; 
 int /*<<< orphan*/  dev_add_pack (TYPE_1__*) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_remove_pack (TYPE_1__*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct stmmac_test_priv*) ; 
 struct stmmac_test_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* stmmac_test_get_udp_skb (struct stmmac_priv*,struct stmmac_packet_attrs*) ; 
 int /*<<< orphan*/  stmmac_test_loopback_validate ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __stmmac_test_loopback(struct stmmac_priv *priv,
				  struct stmmac_packet_attrs *attr)
{
	struct stmmac_test_priv *tpriv;
	struct sk_buff *skb = NULL;
	int ret = 0;

	tpriv = kzalloc(sizeof(*tpriv), GFP_KERNEL);
	if (!tpriv)
		return -ENOMEM;

	tpriv->ok = false;
	init_completion(&tpriv->comp);

	tpriv->pt.type = htons(ETH_P_IP);
	tpriv->pt.func = stmmac_test_loopback_validate;
	tpriv->pt.dev = priv->dev;
	tpriv->pt.af_packet_priv = tpriv;
	tpriv->packet = attr;

	if (!attr->dont_wait)
		dev_add_pack(&tpriv->pt);

	skb = stmmac_test_get_udp_skb(priv, attr);
	if (!skb) {
		ret = -ENOMEM;
		goto cleanup;
	}

	skb_set_queue_mapping(skb, attr->queue_mapping);
	ret = dev_queue_xmit(skb);
	if (ret)
		goto cleanup;

	if (attr->dont_wait)
		goto cleanup;

	if (!attr->timeout)
		attr->timeout = STMMAC_LB_TIMEOUT;

	wait_for_completion_timeout(&tpriv->comp, attr->timeout);
	ret = tpriv->ok ? 0 : -ETIMEDOUT;

cleanup:
	if (!attr->dont_wait)
		dev_remove_pack(&tpriv->pt);
	kfree(tpriv);
	return ret;
}