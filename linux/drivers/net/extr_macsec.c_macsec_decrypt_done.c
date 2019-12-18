#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int len; struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct macsec_rx_sc {int dummy; } ;
struct macsec_rx_sa {struct macsec_rx_sc* sc; } ;
struct TYPE_5__ {int /*<<< orphan*/  netdev; int /*<<< orphan*/  icv_len; } ;
struct macsec_dev {int /*<<< orphan*/  gro_cells; TYPE_2__ secy; } ;
struct crypto_async_request {struct sk_buff* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  packet_number; } ;
struct TYPE_4__ {int valid; int /*<<< orphan*/  has_sci; int /*<<< orphan*/  req; struct macsec_rx_sa* rx_sa; } ;

/* Variables and functions */
 scalar_t__ NET_RX_SUCCESS ; 
 int /*<<< orphan*/  aead_request_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_rx (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 scalar_t__ gro_cells_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 TYPE_3__* macsec_ethhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  macsec_extra_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macsec_finalize_skb (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macsec_post_decrypt (struct sk_buff*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct macsec_dev* macsec_priv (struct net_device*) ; 
 int /*<<< orphan*/  macsec_reset_skb (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macsec_rxsa_put (struct macsec_rx_sa*) ; 
 int /*<<< orphan*/  macsec_rxsc_put (struct macsec_rx_sc*) ; 
 TYPE_1__* macsec_skb_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 

__attribute__((used)) static void macsec_decrypt_done(struct crypto_async_request *base, int err)
{
	struct sk_buff *skb = base->data;
	struct net_device *dev = skb->dev;
	struct macsec_dev *macsec = macsec_priv(dev);
	struct macsec_rx_sa *rx_sa = macsec_skb_cb(skb)->rx_sa;
	struct macsec_rx_sc *rx_sc = rx_sa->sc;
	int len;
	u32 pn;

	aead_request_free(macsec_skb_cb(skb)->req);

	if (!err)
		macsec_skb_cb(skb)->valid = true;

	rcu_read_lock_bh();
	pn = ntohl(macsec_ethhdr(skb)->packet_number);
	if (!macsec_post_decrypt(skb, &macsec->secy, pn)) {
		rcu_read_unlock_bh();
		kfree_skb(skb);
		goto out;
	}

	macsec_finalize_skb(skb, macsec->secy.icv_len,
			    macsec_extra_len(macsec_skb_cb(skb)->has_sci));
	macsec_reset_skb(skb, macsec->secy.netdev);

	len = skb->len;
	if (gro_cells_receive(&macsec->gro_cells, skb) == NET_RX_SUCCESS)
		count_rx(dev, len);

	rcu_read_unlock_bh();

out:
	macsec_rxsa_put(rx_sa);
	macsec_rxsc_put(rx_sc);
	dev_put(dev);
}