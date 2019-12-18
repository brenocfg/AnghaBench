#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct ena_eth_io_tx_desc {int dummy; } ;
struct ena_eth_io_rx_desc {int dummy; } ;
struct TYPE_9__ {int desc_list_entry_size; scalar_t__ max_entries_in_tx_burst; int /*<<< orphan*/  descs_num_before_header; } ;
struct TYPE_7__ {int /*<<< orphan*/  descs_left_in_line; TYPE_2__* curr_bounce_buf; } ;
struct TYPE_11__ {size_t buffer_size; size_t buffers_num; void* base_buffer; scalar_t__ next_to_use; } ;
struct TYPE_8__ {void* virt_addr; int /*<<< orphan*/  phys_addr; } ;
struct ena_com_io_sq {int desc_entry_size; scalar_t__ direction; size_t q_depth; scalar_t__ mem_queue_type; scalar_t__ entries_in_tx_burst_left; int phase; scalar_t__ next_to_comp; scalar_t__ tail; TYPE_3__ llq_info; TYPE_1__ llq_buf_ctrl; TYPE_6__ bounce_buf_ctrl; TYPE_2__ desc_addr; scalar_t__ dma_addr_bits; } ;
struct TYPE_10__ {size_t desc_list_entry_size; } ;
struct ena_com_dev {TYPE_4__ llq_info; int /*<<< orphan*/  dmadev; scalar_t__ dma_addr_bits; } ;
struct ena_com_create_io_ctx {int numa_node; } ;

/* Variables and functions */
 scalar_t__ ENA_ADMIN_PLACEMENT_POLICY_DEV ; 
 scalar_t__ ENA_ADMIN_PLACEMENT_POLICY_HOST ; 
 size_t ENA_COM_BOUNCE_BUFFER_CNTRL_CNT ; 
 scalar_t__ ENA_COM_IO_QUEUE_DIRECTION_TX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dev_to_node (int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ena_com_get_next_bounce_buffer (TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  set_dev_node (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ena_com_init_io_sq(struct ena_com_dev *ena_dev,
			      struct ena_com_create_io_ctx *ctx,
			      struct ena_com_io_sq *io_sq)
{
	size_t size;
	int dev_node = 0;

	memset(&io_sq->desc_addr, 0x0, sizeof(io_sq->desc_addr));

	io_sq->dma_addr_bits = (u8)ena_dev->dma_addr_bits;
	io_sq->desc_entry_size =
		(io_sq->direction == ENA_COM_IO_QUEUE_DIRECTION_TX) ?
		sizeof(struct ena_eth_io_tx_desc) :
		sizeof(struct ena_eth_io_rx_desc);

	size = io_sq->desc_entry_size * io_sq->q_depth;

	if (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_HOST) {
		dev_node = dev_to_node(ena_dev->dmadev);
		set_dev_node(ena_dev->dmadev, ctx->numa_node);
		io_sq->desc_addr.virt_addr =
			dma_alloc_coherent(ena_dev->dmadev, size,
					   &io_sq->desc_addr.phys_addr,
					   GFP_KERNEL);
		set_dev_node(ena_dev->dmadev, dev_node);
		if (!io_sq->desc_addr.virt_addr) {
			io_sq->desc_addr.virt_addr =
				dma_alloc_coherent(ena_dev->dmadev, size,
						   &io_sq->desc_addr.phys_addr,
						   GFP_KERNEL);
		}

		if (!io_sq->desc_addr.virt_addr) {
			pr_err("memory allocation failed\n");
			return -ENOMEM;
		}
	}

	if (io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV) {
		/* Allocate bounce buffers */
		io_sq->bounce_buf_ctrl.buffer_size =
			ena_dev->llq_info.desc_list_entry_size;
		io_sq->bounce_buf_ctrl.buffers_num =
			ENA_COM_BOUNCE_BUFFER_CNTRL_CNT;
		io_sq->bounce_buf_ctrl.next_to_use = 0;

		size = io_sq->bounce_buf_ctrl.buffer_size *
			 io_sq->bounce_buf_ctrl.buffers_num;

		dev_node = dev_to_node(ena_dev->dmadev);
		set_dev_node(ena_dev->dmadev, ctx->numa_node);
		io_sq->bounce_buf_ctrl.base_buffer =
			devm_kzalloc(ena_dev->dmadev, size, GFP_KERNEL);
		set_dev_node(ena_dev->dmadev, dev_node);
		if (!io_sq->bounce_buf_ctrl.base_buffer)
			io_sq->bounce_buf_ctrl.base_buffer =
				devm_kzalloc(ena_dev->dmadev, size, GFP_KERNEL);

		if (!io_sq->bounce_buf_ctrl.base_buffer) {
			pr_err("bounce buffer memory allocation failed\n");
			return -ENOMEM;
		}

		memcpy(&io_sq->llq_info, &ena_dev->llq_info,
		       sizeof(io_sq->llq_info));

		/* Initiate the first bounce buffer */
		io_sq->llq_buf_ctrl.curr_bounce_buf =
			ena_com_get_next_bounce_buffer(&io_sq->bounce_buf_ctrl);
		memset(io_sq->llq_buf_ctrl.curr_bounce_buf,
		       0x0, io_sq->llq_info.desc_list_entry_size);
		io_sq->llq_buf_ctrl.descs_left_in_line =
			io_sq->llq_info.descs_num_before_header;

		if (io_sq->llq_info.max_entries_in_tx_burst > 0)
			io_sq->entries_in_tx_burst_left =
				io_sq->llq_info.max_entries_in_tx_burst;
	}

	io_sq->tail = 0;
	io_sq->next_to_comp = 0;
	io_sq->phase = 1;

	return 0;
}