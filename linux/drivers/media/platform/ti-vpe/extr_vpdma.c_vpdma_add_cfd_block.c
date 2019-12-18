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
typedef  void* u32 ;
struct TYPE_2__ {void* addr; int size; } ;
struct vpdma_desc_list {struct vpdma_cfd* next; TYPE_1__ buf; } ;
struct vpdma_cfd {int block_len; int /*<<< orphan*/  ctl_payload_len; void* payload_addr; void* dest_addr_offset; } ;
struct vpdma_buf {int size; int dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFD_CLS_BLOCK ; 
 int /*<<< orphan*/  CFD_INDIRECT ; 
 int VPDMA_DESC_ALIGN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cfd_pkt_payload_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dump_cfd (struct vpdma_cfd*) ; 

void vpdma_add_cfd_block(struct vpdma_desc_list *list, int client,
		struct vpdma_buf *blk, u32 dest_offset)
{
	struct vpdma_cfd *cfd;
	int len = blk->size;

	WARN_ON(blk->dma_addr & VPDMA_DESC_ALIGN);

	cfd = list->next;
	WARN_ON((void *)(cfd + 1) > (list->buf.addr + list->buf.size));

	cfd->dest_addr_offset = dest_offset;
	cfd->block_len = len;
	cfd->payload_addr = (u32) blk->dma_addr;
	cfd->ctl_payload_len = cfd_pkt_payload_len(CFD_INDIRECT, CFD_CLS_BLOCK,
				client, len >> 4);

	list->next = cfd + 1;

	dump_cfd(cfd);
}