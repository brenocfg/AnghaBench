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
typedef  scalar_t__ u8 ;
struct sq_gather_subdesc {int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int q_len; } ;
struct snd_queue {TYPE_1__ dmem; } ;
struct nicvf {TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_SKIP_CPU_SYNC ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ GET_SQ_DESC (struct snd_queue*,int) ; 
 int /*<<< orphan*/  dma_unmap_page_attrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void nicvf_unmap_sndq_buffers(struct nicvf *nic, struct snd_queue *sq,
			      int hdr_sqe, u8 subdesc_cnt)
{
	u8 idx;
	struct sq_gather_subdesc *gather;

	/* Unmap DMA mapped skb data buffers */
	for (idx = 0; idx < subdesc_cnt; idx++) {
		hdr_sqe++;
		hdr_sqe &= (sq->dmem.q_len - 1);
		gather = (struct sq_gather_subdesc *)GET_SQ_DESC(sq, hdr_sqe);
		/* HW will ensure data coherency, CPU sync not required */
		dma_unmap_page_attrs(&nic->pdev->dev, gather->addr,
				     gather->size, DMA_TO_DEVICE,
				     DMA_ATTR_SKIP_CPU_SYNC);
	}
}