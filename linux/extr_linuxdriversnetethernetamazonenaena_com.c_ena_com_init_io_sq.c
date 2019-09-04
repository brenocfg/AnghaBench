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
struct ena_eth_io_tx_desc {int dummy; } ;
struct ena_eth_io_rx_desc {int dummy; } ;
struct TYPE_2__ {void* virt_addr; int /*<<< orphan*/  phys_addr; } ;
struct ena_com_io_sq {int desc_entry_size; scalar_t__ direction; size_t q_depth; scalar_t__ mem_queue_type; int phase; scalar_t__ next_to_comp; scalar_t__ tail; TYPE_1__ desc_addr; int /*<<< orphan*/  dma_addr_bits; } ;
struct ena_com_dev {int /*<<< orphan*/  dmadev; int /*<<< orphan*/  dma_addr_bits; } ;
struct ena_com_create_io_ctx {int numa_node; } ;

/* Variables and functions */
 scalar_t__ ENA_ADMIN_PLACEMENT_POLICY_HOST ; 
 scalar_t__ ENA_COM_IO_QUEUE_DIRECTION_TX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dev_to_node (int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 void* dma_zalloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  set_dev_node (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ena_com_init_io_sq(struct ena_com_dev *ena_dev,
			      struct ena_com_create_io_ctx *ctx,
			      struct ena_com_io_sq *io_sq)
{
	size_t size;
	int dev_node = 0;

	memset(&io_sq->desc_addr, 0x0, sizeof(io_sq->desc_addr));

	io_sq->dma_addr_bits = ena_dev->dma_addr_bits;
	io_sq->desc_entry_size =
		(io_sq->direction == ENA_COM_IO_QUEUE_DIRECTION_TX) ?
		sizeof(struct ena_eth_io_tx_desc) :
		sizeof(struct ena_eth_io_rx_desc);

	size = io_sq->desc_entry_size * io_sq->q_depth;

	if (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_HOST) {
		dev_node = dev_to_node(ena_dev->dmadev);
		set_dev_node(ena_dev->dmadev, ctx->numa_node);
		io_sq->desc_addr.virt_addr =
			dma_zalloc_coherent(ena_dev->dmadev, size,
					    &io_sq->desc_addr.phys_addr,
					    GFP_KERNEL);
		set_dev_node(ena_dev->dmadev, dev_node);
		if (!io_sq->desc_addr.virt_addr) {
			io_sq->desc_addr.virt_addr =
				dma_zalloc_coherent(ena_dev->dmadev, size,
						    &io_sq->desc_addr.phys_addr,
						    GFP_KERNEL);
		}
	} else {
		dev_node = dev_to_node(ena_dev->dmadev);
		set_dev_node(ena_dev->dmadev, ctx->numa_node);
		io_sq->desc_addr.virt_addr =
			devm_kzalloc(ena_dev->dmadev, size, GFP_KERNEL);
		set_dev_node(ena_dev->dmadev, dev_node);
		if (!io_sq->desc_addr.virt_addr) {
			io_sq->desc_addr.virt_addr =
				devm_kzalloc(ena_dev->dmadev, size, GFP_KERNEL);
		}
	}

	if (!io_sq->desc_addr.virt_addr) {
		pr_err("memory allocation failed");
		return -ENOMEM;
	}

	io_sq->tail = 0;
	io_sq->next_to_comp = 0;
	io_sq->phase = 1;

	return 0;
}