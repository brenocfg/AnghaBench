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
struct sk_buff {int len; struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct macsec_tx_sa {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_sc; } ;
struct macsec_dev {TYPE_1__ secy; } ;
struct crypto_async_request {struct sk_buff* data; } ;
struct TYPE_4__ {struct macsec_tx_sa* tx_sa; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int /*<<< orphan*/  aead_request_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_tx (struct net_device*,int,int) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  macsec_count_tx (struct sk_buff*,int /*<<< orphan*/ *,struct macsec_tx_sa*) ; 
 int /*<<< orphan*/  macsec_encrypt_finish (struct sk_buff*,struct net_device*) ; 
 struct macsec_dev* macsec_priv (struct net_device*) ; 
 TYPE_2__* macsec_skb_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  macsec_txsa_put (struct macsec_tx_sa*) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 

__attribute__((used)) static void macsec_encrypt_done(struct crypto_async_request *base, int err)
{
	struct sk_buff *skb = base->data;
	struct net_device *dev = skb->dev;
	struct macsec_dev *macsec = macsec_priv(dev);
	struct macsec_tx_sa *sa = macsec_skb_cb(skb)->tx_sa;
	int len, ret;

	aead_request_free(macsec_skb_cb(skb)->req);

	rcu_read_lock_bh();
	macsec_encrypt_finish(skb, dev);
	macsec_count_tx(skb, &macsec->secy.tx_sc, macsec_skb_cb(skb)->tx_sa);
	len = skb->len;
	ret = dev_queue_xmit(skb);
	count_tx(dev, ret, len);
	rcu_read_unlock_bh();

	macsec_txsa_put(sa);
	dev_put(dev);
}