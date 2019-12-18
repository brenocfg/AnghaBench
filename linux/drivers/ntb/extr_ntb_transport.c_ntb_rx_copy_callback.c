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
struct ntb_transport_qp {int rx_buff; int rx_max_frame; int rx_index; int /*<<< orphan*/  rx_memcpy; } ;
struct ntb_queue_entry {struct ntb_transport_qp* qp; int /*<<< orphan*/  flags; int /*<<< orphan*/  errors; } ;
struct dmaengine_result {int result; } ;
typedef  enum dmaengine_tx_result { ____Placeholder_dmaengine_tx_result } dmaengine_tx_result ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_DONE_FLAG ; 
#define  DMA_TRANS_ABORTED 131 
#define  DMA_TRANS_NOERROR 130 
#define  DMA_TRANS_READ_FAILED 129 
#define  DMA_TRANS_WRITE_FAILED 128 
 int /*<<< orphan*/  ntb_complete_rxc (struct ntb_transport_qp*) ; 
 int /*<<< orphan*/  ntb_memcpy_rx (struct ntb_queue_entry*,void*) ; 

__attribute__((used)) static void ntb_rx_copy_callback(void *data,
				 const struct dmaengine_result *res)
{
	struct ntb_queue_entry *entry = data;

	/* we need to check DMA results if we are using DMA */
	if (res) {
		enum dmaengine_tx_result dma_err = res->result;

		switch (dma_err) {
		case DMA_TRANS_READ_FAILED:
		case DMA_TRANS_WRITE_FAILED:
			entry->errors++;
			/* fall through */
		case DMA_TRANS_ABORTED:
		{
			struct ntb_transport_qp *qp = entry->qp;
			void *offset = qp->rx_buff + qp->rx_max_frame *
					qp->rx_index;

			ntb_memcpy_rx(entry, offset);
			qp->rx_memcpy++;
			return;
		}

		case DMA_TRANS_NOERROR:
		default:
			break;
		}
	}

	entry->flags |= DESC_DONE_FLAG;

	ntb_complete_rxc(entry->qp);
}