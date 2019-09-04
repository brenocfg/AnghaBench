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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {void* addr; int size; } ;
struct vpdma_desc_list {struct vpdma_cfd* next; TYPE_1__ buf; } ;
struct vpdma_cfd {int /*<<< orphan*/  ctl_payload_len; scalar_t__ payload_addr; scalar_t__ w1; scalar_t__ w0; } ;
struct vpdma_buf {unsigned int size; unsigned int dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CFD_CLS_ADB ; 
 int /*<<< orphan*/  CFD_INDIRECT ; 
 unsigned int VPDMA_ADB_SIZE_ALIGN ; 
 unsigned int VPDMA_DESC_ALIGN ; 
 int /*<<< orphan*/  WARN_ON (unsigned int) ; 
 int /*<<< orphan*/  cfd_pkt_payload_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  dump_cfd (struct vpdma_cfd*) ; 

void vpdma_add_cfd_adb(struct vpdma_desc_list *list, int client,
		struct vpdma_buf *adb)
{
	struct vpdma_cfd *cfd;
	unsigned int len = adb->size;

	WARN_ON(len & VPDMA_ADB_SIZE_ALIGN);
	WARN_ON(adb->dma_addr & VPDMA_DESC_ALIGN);

	cfd = list->next;
	BUG_ON((void *)(cfd + 1) > (list->buf.addr + list->buf.size));

	cfd->w0 = 0;
	cfd->w1 = 0;
	cfd->payload_addr = (u32) adb->dma_addr;
	cfd->ctl_payload_len = cfd_pkt_payload_len(CFD_INDIRECT, CFD_CLS_ADB,
				client, len >> 4);

	list->next = cfd + 1;

	dump_cfd(cfd);
}