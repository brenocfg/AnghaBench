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
typedef  int u32 ;
struct venus_hfi_device {int dummy; } ;
struct TYPE_2__ {int* kva; } ;
struct iface_queue {TYPE_1__ qmem; struct hfi_queue_header* qhdr; } ;
struct hfi_queue_header {int read_idx; int write_idx; int q_size; int tx_req; scalar_t__ rx_req; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcpy (int*,void*,int) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  venus_dump_packet (struct venus_hfi_device*,void*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int venus_write_queue(struct venus_hfi_device *hdev,
			     struct iface_queue *queue,
			     void *packet, u32 *rx_req)
{
	struct hfi_queue_header *qhdr;
	u32 dwords, new_wr_idx;
	u32 empty_space, rd_idx, wr_idx, qsize;
	u32 *wr_ptr;

	if (!queue->qmem.kva)
		return -EINVAL;

	qhdr = queue->qhdr;
	if (!qhdr)
		return -EINVAL;

	venus_dump_packet(hdev, packet);

	dwords = (*(u32 *)packet) >> 2;
	if (!dwords)
		return -EINVAL;

	rd_idx = qhdr->read_idx;
	wr_idx = qhdr->write_idx;
	qsize = qhdr->q_size;
	/* ensure rd/wr indices's are read from memory */
	rmb();

	if (wr_idx >= rd_idx)
		empty_space = qsize - (wr_idx - rd_idx);
	else
		empty_space = rd_idx - wr_idx;

	if (empty_space <= dwords) {
		qhdr->tx_req = 1;
		/* ensure tx_req is updated in memory */
		wmb();
		return -ENOSPC;
	}

	qhdr->tx_req = 0;
	/* ensure tx_req is updated in memory */
	wmb();

	new_wr_idx = wr_idx + dwords;
	wr_ptr = (u32 *)(queue->qmem.kva + (wr_idx << 2));
	if (new_wr_idx < qsize) {
		memcpy(wr_ptr, packet, dwords << 2);
	} else {
		size_t len;

		new_wr_idx -= qsize;
		len = (dwords - new_wr_idx) << 2;
		memcpy(wr_ptr, packet, len);
		memcpy(queue->qmem.kva, packet + len, new_wr_idx << 2);
	}

	/* make sure packet is written before updating the write index */
	wmb();

	qhdr->write_idx = new_wr_idx;
	*rx_req = qhdr->rx_req ? 1 : 0;

	/* make sure write index is updated before an interrupt is raised */
	mb();

	return 0;
}