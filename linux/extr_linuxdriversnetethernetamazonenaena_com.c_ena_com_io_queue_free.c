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
struct TYPE_4__ {int /*<<< orphan*/ * virt_addr; int /*<<< orphan*/  phys_addr; } ;
struct ena_com_io_sq {size_t desc_entry_size; size_t q_depth; scalar_t__ mem_queue_type; TYPE_2__ desc_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/ * virt_addr; int /*<<< orphan*/  phys_addr; } ;
struct ena_com_io_cq {size_t cdesc_entry_size_in_bytes; size_t q_depth; TYPE_1__ cdesc_addr; } ;
struct ena_com_dev {int /*<<< orphan*/  dmadev; } ;

/* Variables and functions */
 scalar_t__ ENA_ADMIN_PLACEMENT_POLICY_HOST ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ena_com_io_queue_free(struct ena_com_dev *ena_dev,
				  struct ena_com_io_sq *io_sq,
				  struct ena_com_io_cq *io_cq)
{
	size_t size;

	if (io_cq->cdesc_addr.virt_addr) {
		size = io_cq->cdesc_entry_size_in_bytes * io_cq->q_depth;

		dma_free_coherent(ena_dev->dmadev, size,
				  io_cq->cdesc_addr.virt_addr,
				  io_cq->cdesc_addr.phys_addr);

		io_cq->cdesc_addr.virt_addr = NULL;
	}

	if (io_sq->desc_addr.virt_addr) {
		size = io_sq->desc_entry_size * io_sq->q_depth;

		if (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_HOST)
			dma_free_coherent(ena_dev->dmadev, size,
					  io_sq->desc_addr.virt_addr,
					  io_sq->desc_addr.phys_addr);
		else
			devm_kfree(ena_dev->dmadev, io_sq->desc_addr.virt_addr);

		io_sq->desc_addr.virt_addr = NULL;
	}
}