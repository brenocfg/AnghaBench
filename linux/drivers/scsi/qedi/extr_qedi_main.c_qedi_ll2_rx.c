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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct skb_work_list {int /*<<< orphan*/  list; scalar_t__ vlan_id; struct sk_buff* skb; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct qedi_uio_dev {struct qedi_uio_ctrl* uctrl; } ;
struct qedi_uio_ctrl {int dummy; } ;
struct qedi_ctx {int /*<<< orphan*/  ll2_recv_thread; int /*<<< orphan*/  ll2_lock; int /*<<< orphan*/  ll2_skb_list; int /*<<< orphan*/  dbg_ctx; struct qedi_uio_dev* udev; int /*<<< orphan*/  flags; } ;
struct ethhdr {scalar_t__ h_proto; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  QEDI_LOG_LL2 ; 
 int /*<<< orphan*/  QEDI_LOG_UIO ; 
 int /*<<< orphan*/  QEDI_WARN (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  UIO_DEV_OPENED ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  __vlan_insert_tag (struct sk_buff*,scalar_t__,scalar_t__) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct skb_work_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,struct ethhdr*,int) ; 
 scalar_t__ skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedi_ll2_rx(void *cookie, struct sk_buff *skb, u32 arg1, u32 arg2)
{
	struct qedi_ctx *qedi = (struct qedi_ctx *)cookie;
	struct qedi_uio_dev *udev;
	struct qedi_uio_ctrl *uctrl;
	struct skb_work_list *work;
	struct ethhdr *eh;

	if (!qedi) {
		QEDI_ERR(NULL, "qedi is NULL\n");
		return -1;
	}

	if (!test_bit(UIO_DEV_OPENED, &qedi->flags)) {
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_UIO,
			  "UIO DEV is not opened\n");
		kfree_skb(skb);
		return 0;
	}

	eh = (struct ethhdr *)skb->data;
	/* Undo VLAN encapsulation */
	if (eh->h_proto == htons(ETH_P_8021Q)) {
		memmove((u8 *)eh + VLAN_HLEN, eh, ETH_ALEN * 2);
		eh = (struct ethhdr *)skb_pull(skb, VLAN_HLEN);
		skb_reset_mac_header(skb);
	}

	/* Filter out non FIP/FCoE frames here to free them faster */
	if (eh->h_proto != htons(ETH_P_ARP) &&
	    eh->h_proto != htons(ETH_P_IP) &&
	    eh->h_proto != htons(ETH_P_IPV6)) {
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_LL2,
			  "Dropping frame ethertype [0x%x] len [0x%x].\n",
			  eh->h_proto, skb->len);
		kfree_skb(skb);
		return 0;
	}

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_LL2,
		  "Allowed frame ethertype [0x%x] len [0x%x].\n",
		  eh->h_proto, skb->len);

	udev = qedi->udev;
	uctrl = udev->uctrl;

	work = kzalloc(sizeof(*work), GFP_ATOMIC);
	if (!work) {
		QEDI_WARN(&qedi->dbg_ctx,
			  "Could not allocate work so dropping frame.\n");
		kfree_skb(skb);
		return 0;
	}

	INIT_LIST_HEAD(&work->list);
	work->skb = skb;

	if (skb_vlan_tag_present(skb))
		work->vlan_id = skb_vlan_tag_get(skb);

	if (work->vlan_id)
		__vlan_insert_tag(work->skb, htons(ETH_P_8021Q), work->vlan_id);

	spin_lock_bh(&qedi->ll2_lock);
	list_add_tail(&work->list, &qedi->ll2_skb_list);
	spin_unlock_bh(&qedi->ll2_lock);

	wake_up_process(qedi->ll2_recv_thread);

	return 0;
}