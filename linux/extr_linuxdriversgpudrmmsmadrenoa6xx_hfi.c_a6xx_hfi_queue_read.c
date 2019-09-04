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
typedef  size_t u32 ;
struct a6xx_hfi_queue_header {size_t read_index; size_t write_index; int rx_request; size_t size; } ;
struct a6xx_hfi_queue {size_t* data; struct a6xx_hfi_queue_header* header; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int HFI_HEADER_SIZE (size_t) ; 

__attribute__((used)) static int a6xx_hfi_queue_read(struct a6xx_hfi_queue *queue, u32 *data,
		u32 dwords)
{
	struct a6xx_hfi_queue_header *header = queue->header;
	u32 i, hdr, index = header->read_index;

	if (header->read_index == header->write_index) {
		header->rx_request = 1;
		return 0;
	}

	hdr = queue->data[index];

	/*
	 * If we are to assume that the GMU firmware is in fact a rational actor
	 * and is programmed to not send us a larger response than we expect
	 * then we can also assume that if the header size is unexpectedly large
	 * that it is due to memory corruption and/or hardware failure. In this
	 * case the only reasonable course of action is to BUG() to help harden
	 * the failure.
	 */

	BUG_ON(HFI_HEADER_SIZE(hdr) > dwords);

	for (i = 0; i < HFI_HEADER_SIZE(hdr); i++) {
		data[i] = queue->data[index];
		index = (index + 1) % header->size;
	}

	header->read_index = index;
	return HFI_HEADER_SIZE(hdr);
}