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
struct vnic_wq_buf {scalar_t__ os_buf; int /*<<< orphan*/  len; int /*<<< orphan*/  dma_addr; scalar_t__ sop; } ;
struct vnic_wq {int /*<<< orphan*/  vdev; } ;
struct enic {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (scalar_t__) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct enic* vnic_dev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enic_free_wq_buf(struct vnic_wq *wq, struct vnic_wq_buf *buf)
{
	struct enic *enic = vnic_dev_priv(wq->vdev);

	if (buf->sop)
		pci_unmap_single(enic->pdev, buf->dma_addr,
			buf->len, PCI_DMA_TODEVICE);
	else
		pci_unmap_page(enic->pdev, buf->dma_addr,
			buf->len, PCI_DMA_TODEVICE);

	if (buf->os_buf)
		dev_kfree_skb_any(buf->os_buf);
}