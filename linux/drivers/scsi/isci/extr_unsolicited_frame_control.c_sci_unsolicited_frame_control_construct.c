#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int physical_address; int /*<<< orphan*/ * array; } ;
struct TYPE_5__ {int physical_address; int* array; } ;
struct TYPE_4__ {struct sci_unsolicited_frame* array; } ;
struct sci_unsolicited_frame_control {TYPE_3__ headers; TYPE_2__ address_table; TYPE_1__ buffers; scalar_t__ get; } ;
struct sci_unsolicited_frame {int /*<<< orphan*/  state; int /*<<< orphan*/ * header; void* buffer; } ;
struct isci_host {int ufi_dma; void* ufi_buf; struct sci_unsolicited_frame_control uf_control; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int SCI_UFI_BUF_SIZE ; 
 int SCI_UFI_HDR_SIZE ; 
 int SCU_MAX_UNSOLICITED_FRAMES ; 
 int SCU_UNSOLICITED_FRAME_BUFFER_SIZE ; 
 int /*<<< orphan*/  UNSOLICITED_FRAME_EMPTY ; 

void sci_unsolicited_frame_control_construct(struct isci_host *ihost)
{
	struct sci_unsolicited_frame_control *uf_control = &ihost->uf_control;
	struct sci_unsolicited_frame *uf;
	dma_addr_t dma = ihost->ufi_dma;
	void *virt = ihost->ufi_buf;
	int i;

	/*
	 * The Unsolicited Frame buffers are set at the start of the UF
	 * memory descriptor entry. The headers and address table will be
	 * placed after the buffers.
	 */

	/*
	 * Program the location of the UF header table into the SCU.
	 * Notes:
	 * - The address must align on a 64-byte boundary. Guaranteed to be
	 *   on 64-byte boundary already 1KB boundary for unsolicited frames.
	 * - Program unused header entries to overlap with the last
	 *   unsolicited frame.  The silicon will never DMA to these unused
	 *   headers, since we program the UF address table pointers to
	 *   NULL.
	 */
	uf_control->headers.physical_address = dma + SCI_UFI_BUF_SIZE;
	uf_control->headers.array = virt + SCI_UFI_BUF_SIZE;

	/*
	 * Program the location of the UF address table into the SCU.
	 * Notes:
	 * - The address must align on a 64-bit boundary. Guaranteed to be on 64
	 *   byte boundary already due to above programming headers being on a
	 *   64-bit boundary and headers are on a 64-bytes in size.
	 */
	uf_control->address_table.physical_address = dma + SCI_UFI_BUF_SIZE + SCI_UFI_HDR_SIZE;
	uf_control->address_table.array = virt + SCI_UFI_BUF_SIZE + SCI_UFI_HDR_SIZE;
	uf_control->get = 0;

	/*
	 * UF buffer requirements are:
	 * - The last entry in the UF queue is not NULL.
	 * - There is a power of 2 number of entries (NULL or not-NULL)
	 *   programmed into the queue.
	 * - Aligned on a 1KB boundary. */

	/*
	 * Program the actual used UF buffers into the UF address table and
	 * the controller's array of UFs.
	 */
	for (i = 0; i < SCU_MAX_UNSOLICITED_FRAMES; i++) {
		uf = &uf_control->buffers.array[i];

		uf_control->address_table.array[i] = dma;

		uf->buffer = virt;
		uf->header = &uf_control->headers.array[i];
		uf->state  = UNSOLICITED_FRAME_EMPTY;

		/*
		 * Increment the address of the physical and virtual memory
		 * pointers. Everything is aligned on 1k boundary with an
		 * increment of 1k.
		 */
		virt += SCU_UNSOLICITED_FRAME_BUFFER_SIZE;
		dma += SCU_UNSOLICITED_FRAME_BUFFER_SIZE;
	}
}