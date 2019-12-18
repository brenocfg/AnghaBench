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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_window_errors; } ;
struct net_device {TYPE_2__ stats; struct airo_info* ml_priv; } ;
struct TYPE_3__ {int fid; struct sk_buff* skb; } ;
struct airo_info {int* fids; int /*<<< orphan*/  sem; int /*<<< orphan*/  flags; int /*<<< orphan*/  jobs; TYPE_1__ xmit11; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_PENDING_XMIT11 ; 
 int /*<<< orphan*/  JOB_XMIT11 ; 
 int MAX_FIDS ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ transmit_802_11_packet (struct airo_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void airo_end_xmit11(struct net_device *dev) {
	u16 status;
	int i;
	struct airo_info *priv = dev->ml_priv;
	struct sk_buff *skb = priv->xmit11.skb;
	int fid = priv->xmit11.fid;
	u32 *fids = priv->fids;

	clear_bit(JOB_XMIT11, &priv->jobs);
	clear_bit(FLAG_PENDING_XMIT11, &priv->flags);
	status = transmit_802_11_packet (priv, fids[fid], skb->data);
	up(&priv->sem);

	i = MAX_FIDS / 2;
	if ( status == SUCCESS ) {
		netif_trans_update(dev);
		for (; i < MAX_FIDS && (priv->fids[i] & 0xffff0000); i++);
	} else {
		priv->fids[fid] &= 0xffff;
		dev->stats.tx_window_errors++;
	}
	if (i < MAX_FIDS)
		netif_wake_queue(dev);
	dev_kfree_skb(skb);
}