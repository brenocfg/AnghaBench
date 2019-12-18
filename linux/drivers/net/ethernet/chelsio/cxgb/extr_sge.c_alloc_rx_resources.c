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
struct skb_shared_info {int dummy; } ;
struct sge_params {int* freelQ_size; } ;
struct TYPE_4__ {int genbit; int size; void* entries; int /*<<< orphan*/  dma_addr; scalar_t__ credits; } ;
struct sge {size_t jumbo_fl; TYPE_2__ respQ; struct freelQ* freelQ; scalar_t__ rx_pkt_pad; TYPE_1__* adapter; } ;
struct respQ_e {int dummy; } ;
struct pci_dev {int dummy; } ;
struct freelQ_e {int dummy; } ;
struct freelQ_ce {int dummy; } ;
struct freelQ {int genbit; int size; unsigned int dma_offset; unsigned int rx_buffer_size; int recycleq_idx; int /*<<< orphan*/  centries; void* entries; int /*<<< orphan*/  dma_addr; } ;
struct cpl_rx_data {int dummy; } ;
struct TYPE_3__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int NET_IP_ALIGN ; 
 unsigned int SGE_FREELQ_N ; 
 int SGE_RESPQ_E_N ; 
 unsigned int SGE_RX_SM_BUF_SIZE ; 
 int SKB_DATA_ALIGN (int) ; 
 int /*<<< orphan*/  free_rx_resources (struct sge*) ; 
 int /*<<< orphan*/  kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 void* pci_alloc_consistent (struct pci_dev*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_rx_resources(struct sge *sge, struct sge_params *p)
{
	struct pci_dev *pdev = sge->adapter->pdev;
	unsigned int size, i;

	for (i = 0; i < SGE_FREELQ_N; i++) {
		struct freelQ *q = &sge->freelQ[i];

		q->genbit = 1;
		q->size = p->freelQ_size[i];
		q->dma_offset = sge->rx_pkt_pad ? 0 : NET_IP_ALIGN;
		size = sizeof(struct freelQ_e) * q->size;
		q->entries = pci_alloc_consistent(pdev, size, &q->dma_addr);
		if (!q->entries)
			goto err_no_mem;

		size = sizeof(struct freelQ_ce) * q->size;
		q->centries = kzalloc(size, GFP_KERNEL);
		if (!q->centries)
			goto err_no_mem;
	}

	/*
	 * Calculate the buffer sizes for the two free lists.  FL0 accommodates
	 * regular sized Ethernet frames, FL1 is sized not to exceed 16K,
	 * including all the sk_buff overhead.
	 *
	 * Note: For T2 FL0 and FL1 are reversed.
	 */
	sge->freelQ[!sge->jumbo_fl].rx_buffer_size = SGE_RX_SM_BUF_SIZE +
		sizeof(struct cpl_rx_data) +
		sge->freelQ[!sge->jumbo_fl].dma_offset;

	size = (16 * 1024) - SKB_DATA_ALIGN(sizeof(struct skb_shared_info));

	sge->freelQ[sge->jumbo_fl].rx_buffer_size = size;

	/*
	 * Setup which skb recycle Q should be used when recycling buffers from
	 * each free list.
	 */
	sge->freelQ[!sge->jumbo_fl].recycleq_idx = 0;
	sge->freelQ[sge->jumbo_fl].recycleq_idx = 1;

	sge->respQ.genbit = 1;
	sge->respQ.size = SGE_RESPQ_E_N;
	sge->respQ.credits = 0;
	size = sizeof(struct respQ_e) * sge->respQ.size;
	sge->respQ.entries =
		pci_alloc_consistent(pdev, size, &sge->respQ.dma_addr);
	if (!sge->respQ.entries)
		goto err_no_mem;
	return 0;

err_no_mem:
	free_rx_resources(sge);
	return -ENOMEM;
}