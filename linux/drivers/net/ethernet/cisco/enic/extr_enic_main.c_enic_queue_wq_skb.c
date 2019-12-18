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
struct vnic_wq_buf {TYPE_2__* next; struct vnic_wq_buf* prev; int /*<<< orphan*/  os_buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  desc_avail; } ;
struct vnic_wq {TYPE_2__* to_use; TYPE_1__ ring; TYPE_2__* to_clean; } ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ encapsulation; } ;
struct enic {unsigned int loop_tag; scalar_t__ loop_enable; } ;
struct TYPE_6__ {unsigned int gso_size; } ;
struct TYPE_5__ {struct vnic_wq_buf* prev; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  enic_free_wq_buf (struct vnic_wq*,struct vnic_wq_buf*) ; 
 int enic_queue_wq_skb_csum_l4 (struct enic*,struct vnic_wq*,struct sk_buff*,int,unsigned int,int) ; 
 int enic_queue_wq_skb_encap (struct enic*,struct vnic_wq*,struct sk_buff*,int,unsigned int,int) ; 
 int enic_queue_wq_skb_tso (struct enic*,struct vnic_wq*,struct sk_buff*,unsigned int,int,unsigned int,int) ; 
 int enic_queue_wq_skb_vlan (struct enic*,struct vnic_wq*,struct sk_buff*,int,unsigned int,int) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 unsigned int skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void enic_queue_wq_skb(struct enic *enic,
	struct vnic_wq *wq, struct sk_buff *skb)
{
	unsigned int mss = skb_shinfo(skb)->gso_size;
	unsigned int vlan_tag = 0;
	int vlan_tag_insert = 0;
	int loopback = 0;
	int err;

	if (skb_vlan_tag_present(skb)) {
		/* VLAN tag from trunking driver */
		vlan_tag_insert = 1;
		vlan_tag = skb_vlan_tag_get(skb);
	} else if (enic->loop_enable) {
		vlan_tag = enic->loop_tag;
		loopback = 1;
	}

	if (mss)
		err = enic_queue_wq_skb_tso(enic, wq, skb, mss,
					    vlan_tag_insert, vlan_tag,
					    loopback);
	else if (skb->encapsulation)
		err = enic_queue_wq_skb_encap(enic, wq, skb, vlan_tag_insert,
					      vlan_tag, loopback);
	else if	(skb->ip_summed == CHECKSUM_PARTIAL)
		err = enic_queue_wq_skb_csum_l4(enic, wq, skb, vlan_tag_insert,
						vlan_tag, loopback);
	else
		err = enic_queue_wq_skb_vlan(enic, wq, skb, vlan_tag_insert,
					     vlan_tag, loopback);
	if (unlikely(err)) {
		struct vnic_wq_buf *buf;

		buf = wq->to_use->prev;
		/* while not EOP of previous pkt && queue not empty.
		 * For all non EOP bufs, os_buf is NULL.
		 */
		while (!buf->os_buf && (buf->next != wq->to_clean)) {
			enic_free_wq_buf(wq, buf);
			wq->ring.desc_avail++;
			buf = buf->prev;
		}
		wq->to_use = buf->next;
		dev_kfree_skb(skb);
	}
}