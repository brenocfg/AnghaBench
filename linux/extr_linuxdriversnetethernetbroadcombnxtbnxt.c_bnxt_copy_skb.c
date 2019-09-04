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
struct sk_buff {int data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bnxt_napi {int /*<<< orphan*/  napi; struct bnxt* bp; } ;
struct bnxt {int /*<<< orphan*/  rx_dir; int /*<<< orphan*/  rx_copy_thresh; struct pci_dev* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int NET_IP_ALIGN ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int,int /*<<< orphan*/ *,int) ; 
 struct sk_buff* napi_alloc_skb (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static inline struct sk_buff *bnxt_copy_skb(struct bnxt_napi *bnapi, u8 *data,
					    unsigned int len,
					    dma_addr_t mapping)
{
	struct bnxt *bp = bnapi->bp;
	struct pci_dev *pdev = bp->pdev;
	struct sk_buff *skb;

	skb = napi_alloc_skb(&bnapi->napi, len);
	if (!skb)
		return NULL;

	dma_sync_single_for_cpu(&pdev->dev, mapping, bp->rx_copy_thresh,
				bp->rx_dir);

	memcpy(skb->data - NET_IP_ALIGN, data - NET_IP_ALIGN,
	       len + NET_IP_ALIGN);

	dma_sync_single_for_device(&pdev->dev, mapping, bp->rx_copy_thresh,
				   bp->rx_dir);

	skb_put(skb, len);
	return skb;
}