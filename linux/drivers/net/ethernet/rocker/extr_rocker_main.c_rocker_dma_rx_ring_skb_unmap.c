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
struct rocker_tlv {int dummy; } ;
struct rocker {struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 size_t ROCKER_TLV_RX_FRAG_ADDR ; 
 size_t ROCKER_TLV_RX_FRAG_MAX_LEN ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 size_t rocker_tlv_get_u16 (struct rocker_tlv const*) ; 
 int /*<<< orphan*/  rocker_tlv_get_u64 (struct rocker_tlv const*) ; 

__attribute__((used)) static void rocker_dma_rx_ring_skb_unmap(const struct rocker *rocker,
					 const struct rocker_tlv **attrs)
{
	struct pci_dev *pdev = rocker->pdev;
	dma_addr_t dma_handle;
	size_t len;

	if (!attrs[ROCKER_TLV_RX_FRAG_ADDR] ||
	    !attrs[ROCKER_TLV_RX_FRAG_MAX_LEN])
		return;
	dma_handle = rocker_tlv_get_u64(attrs[ROCKER_TLV_RX_FRAG_ADDR]);
	len = rocker_tlv_get_u16(attrs[ROCKER_TLV_RX_FRAG_MAX_LEN]);
	pci_unmap_single(pdev, dma_handle, len, PCI_DMA_FROMDEVICE);
}