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
struct hfi_queue_header {int status; int q_size; int rx_wm; int tx_wm; int rx_req; scalar_t__ write_idx; scalar_t__ read_idx; scalar_t__ tx_irq_status; scalar_t__ rx_irq_status; scalar_t__ tx_req; scalar_t__ pkt_size; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFACEQ_DFLT_QHDR ; 
 int IFACEQ_QUEUE_SIZE ; 

__attribute__((used)) static void venus_set_qhdr_defaults(struct hfi_queue_header *qhdr)
{
	qhdr->status = 1;
	qhdr->type = IFACEQ_DFLT_QHDR;
	qhdr->q_size = IFACEQ_QUEUE_SIZE / 4;
	qhdr->pkt_size = 0;
	qhdr->rx_wm = 1;
	qhdr->tx_wm = 1;
	qhdr->rx_req = 1;
	qhdr->tx_req = 0;
	qhdr->rx_irq_status = 0;
	qhdr->tx_irq_status = 0;
	qhdr->read_idx = 0;
	qhdr->write_idx = 0;
}