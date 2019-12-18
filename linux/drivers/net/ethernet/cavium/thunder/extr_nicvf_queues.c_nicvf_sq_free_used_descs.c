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
typedef  int u64 ;
struct sq_hdr_subdesc {scalar_t__ subdesc_type; int tot_len; int subdesc_cnt; } ;
struct snd_queue {int head; scalar_t__* skbuff; } ;
struct sk_buff {int dummy; } ;
struct nicvf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  atomic64_t ;

/* Variables and functions */
 scalar_t__ GET_SQ_DESC (struct snd_queue*,int) ; 
 int /*<<< orphan*/  NIC_QSET_SQ_0_7_HEAD ; 
 int /*<<< orphan*/  NIC_QSET_SQ_0_7_TAIL ; 
 scalar_t__ SQ_DESC_TYPE_HEADER ; 
 int /*<<< orphan*/  atomic64_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct nicvf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nicvf_put_sq_desc (struct snd_queue*,int) ; 
 int nicvf_queue_reg_read (struct nicvf*,int /*<<< orphan*/ ,int) ; 

void nicvf_sq_free_used_descs(struct net_device *netdev, struct snd_queue *sq,
			      int qidx)
{
	u64 head, tail;
	struct sk_buff *skb;
	struct nicvf *nic = netdev_priv(netdev);
	struct sq_hdr_subdesc *hdr;

	head = nicvf_queue_reg_read(nic, NIC_QSET_SQ_0_7_HEAD, qidx) >> 4;
	tail = nicvf_queue_reg_read(nic, NIC_QSET_SQ_0_7_TAIL, qidx) >> 4;
	while (sq->head != head) {
		hdr = (struct sq_hdr_subdesc *)GET_SQ_DESC(sq, sq->head);
		if (hdr->subdesc_type != SQ_DESC_TYPE_HEADER) {
			nicvf_put_sq_desc(sq, 1);
			continue;
		}
		skb = (struct sk_buff *)sq->skbuff[sq->head];
		if (skb)
			dev_kfree_skb_any(skb);
		atomic64_add(1, (atomic64_t *)&netdev->stats.tx_packets);
		atomic64_add(hdr->tot_len,
			     (atomic64_t *)&netdev->stats.tx_bytes);
		nicvf_put_sq_desc(sq, hdr->subdesc_cnt + 1);
	}
}