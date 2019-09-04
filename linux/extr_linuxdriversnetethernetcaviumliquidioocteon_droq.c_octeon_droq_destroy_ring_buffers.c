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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct octeon_skb_page_info {scalar_t__ page; scalar_t__ dma; } ;
struct octeon_droq {size_t max_count; TYPE_1__* recv_buf_list; } ;
struct octeon_device {int /*<<< orphan*/  pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * buffer; struct octeon_skb_page_info pg_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  lio_unmap_ring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_droq_reset_indices (struct octeon_droq*) ; 
 int /*<<< orphan*/  recv_buffer_destroy (int /*<<< orphan*/ *,struct octeon_skb_page_info*) ; 

__attribute__((used)) static void
octeon_droq_destroy_ring_buffers(struct octeon_device *oct,
				 struct octeon_droq *droq)
{
	u32 i;
	struct octeon_skb_page_info *pg_info;

	for (i = 0; i < droq->max_count; i++) {
		pg_info = &droq->recv_buf_list[i].pg_info;
		if (!pg_info)
			continue;

		if (pg_info->dma)
			lio_unmap_ring(oct->pci_dev,
				       (u64)pg_info->dma);
		pg_info->dma = 0;

		if (pg_info->page)
			recv_buffer_destroy(droq->recv_buf_list[i].buffer,
					    pg_info);

		droq->recv_buf_list[i].buffer = NULL;
	}

	octeon_droq_reset_indices(droq);
}