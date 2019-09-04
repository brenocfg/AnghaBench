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
typedef  int /*<<< orphan*/  u64 ;
struct scif_p2p_info {int* sg_nentries; int* ppi_len; void** ppi_sg; int /*<<< orphan*/  ppi_peer_id; void** ppi_da; } ;
struct scif_hw_dev {int /*<<< orphan*/  dev; TYPE_2__* aper; TYPE_1__* mmio; } ;
struct scif_dev {int /*<<< orphan*/  node; struct scif_hw_dev* sdev; } ;
struct TYPE_4__ {int len; int /*<<< orphan*/  pa; } ;
struct TYPE_3__ {int len; int /*<<< orphan*/  pa; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 size_t SCIF_PPI_APER ; 
 size_t SCIF_PPI_MMIO ; 
 int dma_map_sg (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 int get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scif_p2p_info*) ; 
 struct scif_p2p_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_p2p_freesg (void*) ; 
 void* scif_p2p_setsg (int /*<<< orphan*/ ,int,int) ; 
 void* sg_dma_address (void*) ; 

__attribute__((used)) static struct scif_p2p_info *
scif_init_p2p_info(struct scif_dev *scifdev, struct scif_dev *peerdev)
{
	struct scif_p2p_info *p2p;
	int num_mmio_pages, num_aper_pages, sg_page_shift, err, num_aper_chunks;
	struct scif_hw_dev *psdev = peerdev->sdev;
	struct scif_hw_dev *sdev = scifdev->sdev;

	num_mmio_pages = psdev->mmio->len >> PAGE_SHIFT;
	num_aper_pages = psdev->aper->len >> PAGE_SHIFT;

	p2p = kzalloc(sizeof(*p2p), GFP_KERNEL);
	if (!p2p)
		return NULL;
	p2p->ppi_sg[SCIF_PPI_MMIO] = scif_p2p_setsg(psdev->mmio->pa,
						    PAGE_SIZE, num_mmio_pages);
	if (!p2p->ppi_sg[SCIF_PPI_MMIO])
		goto free_p2p;
	p2p->sg_nentries[SCIF_PPI_MMIO] = num_mmio_pages;
	sg_page_shift = get_order(min(psdev->aper->len, (u64)(1 << 30)));
	num_aper_chunks = num_aper_pages >> (sg_page_shift - PAGE_SHIFT);
	p2p->ppi_sg[SCIF_PPI_APER] = scif_p2p_setsg(psdev->aper->pa,
						    1 << sg_page_shift,
						    num_aper_chunks);
	p2p->sg_nentries[SCIF_PPI_APER] = num_aper_chunks;
	err = dma_map_sg(&sdev->dev, p2p->ppi_sg[SCIF_PPI_MMIO],
			 num_mmio_pages, PCI_DMA_BIDIRECTIONAL);
	if (err != num_mmio_pages)
		goto scif_p2p_free;
	err = dma_map_sg(&sdev->dev, p2p->ppi_sg[SCIF_PPI_APER],
			 num_aper_chunks, PCI_DMA_BIDIRECTIONAL);
	if (err != num_aper_chunks)
		goto dma_unmap;
	p2p->ppi_da[SCIF_PPI_MMIO] = sg_dma_address(p2p->ppi_sg[SCIF_PPI_MMIO]);
	p2p->ppi_da[SCIF_PPI_APER] = sg_dma_address(p2p->ppi_sg[SCIF_PPI_APER]);
	p2p->ppi_len[SCIF_PPI_MMIO] = num_mmio_pages;
	p2p->ppi_len[SCIF_PPI_APER] = num_aper_pages;
	p2p->ppi_peer_id = peerdev->node;
	return p2p;
dma_unmap:
	dma_unmap_sg(&sdev->dev, p2p->ppi_sg[SCIF_PPI_MMIO],
		     p2p->sg_nentries[SCIF_PPI_MMIO], DMA_BIDIRECTIONAL);
scif_p2p_free:
	scif_p2p_freesg(p2p->ppi_sg[SCIF_PPI_MMIO]);
	scif_p2p_freesg(p2p->ppi_sg[SCIF_PPI_APER]);
free_p2p:
	kfree(p2p);
	return NULL;
}