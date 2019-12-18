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
struct ena_eth_io_tx_cdesc {int dummy; } ;
struct ena_eth_io_rx_cdesc_base {int dummy; } ;
struct TYPE_2__ {void* virt_addr; int /*<<< orphan*/  phys_addr; } ;
struct ena_com_io_cq {int cdesc_entry_size_in_bytes; scalar_t__ direction; size_t q_depth; int phase; scalar_t__ head; TYPE_1__ cdesc_addr; } ;
struct ena_com_dev {int /*<<< orphan*/  dmadev; } ;
struct ena_com_create_io_ctx {int numa_node; } ;

/* Variables and functions */
 scalar_t__ ENA_COM_IO_QUEUE_DIRECTION_TX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dev_to_node (int /*<<< orphan*/ ) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  set_dev_node (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ena_com_init_io_cq(struct ena_com_dev *ena_dev,
			      struct ena_com_create_io_ctx *ctx,
			      struct ena_com_io_cq *io_cq)
{
	size_t size;
	int prev_node = 0;

	memset(&io_cq->cdesc_addr, 0x0, sizeof(io_cq->cdesc_addr));

	/* Use the basic completion descriptor for Rx */
	io_cq->cdesc_entry_size_in_bytes =
		(io_cq->direction == ENA_COM_IO_QUEUE_DIRECTION_TX) ?
		sizeof(struct ena_eth_io_tx_cdesc) :
		sizeof(struct ena_eth_io_rx_cdesc_base);

	size = io_cq->cdesc_entry_size_in_bytes * io_cq->q_depth;

	prev_node = dev_to_node(ena_dev->dmadev);
	set_dev_node(ena_dev->dmadev, ctx->numa_node);
	io_cq->cdesc_addr.virt_addr =
		dma_alloc_coherent(ena_dev->dmadev, size,
				   &io_cq->cdesc_addr.phys_addr, GFP_KERNEL);
	set_dev_node(ena_dev->dmadev, prev_node);
	if (!io_cq->cdesc_addr.virt_addr) {
		io_cq->cdesc_addr.virt_addr =
			dma_alloc_coherent(ena_dev->dmadev, size,
					   &io_cq->cdesc_addr.phys_addr,
					   GFP_KERNEL);
	}

	if (!io_cq->cdesc_addr.virt_addr) {
		pr_err("memory allocation failed\n");
		return -ENOMEM;
	}

	io_cq->phase = 1;
	io_cq->head = 0;

	return 0;
}