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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct qed_hwfn {struct qed_dev* cdev; } ;
struct qed_dev {TYPE_3__* ll2; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  cb_cookie; TYPE_2__* cbs; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* tx_cb ) (int /*<<< orphan*/ ,struct sk_buff*,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sk_buff*,int) ; 

__attribute__((used)) static void qed_ll2b_complete_tx_packet(void *cxt,
					u8 connection_handle,
					void *cookie,
					dma_addr_t first_frag_addr,
					bool b_last_fragment,
					bool b_last_packet)
{
	struct qed_hwfn *p_hwfn = cxt;
	struct qed_dev *cdev = p_hwfn->cdev;
	struct sk_buff *skb = cookie;

	/* All we need to do is release the mapping */
	dma_unmap_single(&p_hwfn->cdev->pdev->dev, first_frag_addr,
			 skb_headlen(skb), DMA_TO_DEVICE);

	if (cdev->ll2->cbs && cdev->ll2->cbs->tx_cb)
		cdev->ll2->cbs->tx_cb(cdev->ll2->cb_cookie, skb,
				      b_last_fragment);

	dev_kfree_skb_any(skb);
}