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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct a6xx_hfi_queue_header {int type; int status; int size; int rx_watermark; int tx_watermark; int rx_request; scalar_t__ write_index; scalar_t__ read_index; scalar_t__ tx_request; scalar_t__ dropped; scalar_t__ msg_size; int /*<<< orphan*/  iova; } ;
struct a6xx_hfi_queue {int /*<<< orphan*/  seqnum; void* data; struct a6xx_hfi_queue_header* header; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int SZ_4K ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void a6xx_hfi_queue_init(struct a6xx_hfi_queue *queue,
		struct a6xx_hfi_queue_header *header, void *virt, u64 iova,
		u32 id)
{
	spin_lock_init(&queue->lock);
	queue->header = header;
	queue->data = virt;
	atomic_set(&queue->seqnum, 0);

	/* Set up the shared memory header */
	header->iova = iova;
	header->type =  10 << 8 | id;
	header->status = 1;
	header->size = SZ_4K >> 2;
	header->msg_size = 0;
	header->dropped = 0;
	header->rx_watermark = 1;
	header->tx_watermark = 1;
	header->rx_request = 1;
	header->tx_request = 0;
	header->read_index = 0;
	header->write_index = 0;
}