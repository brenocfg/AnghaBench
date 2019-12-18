#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct vmci_guest_device {int /*<<< orphan*/ * data_buffer; scalar_t__ iobase; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ resource; } ;
struct TYPE_3__ {scalar_t__ context; } ;
struct vmci_datagram {TYPE_2__ dst; TYPE_1__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 size_t PAGE_SIZE ; 
 scalar_t__ VMCI_DATA_IN_ADDR ; 
 size_t VMCI_DG_HEADERSIZE ; 
 unsigned int VMCI_DG_SIZE_ALIGNED (struct vmci_datagram*) ; 
 scalar_t__ VMCI_EVENT_HANDLER ; 
 scalar_t__ VMCI_HYPERVISOR_CONTEXT_ID ; 
 scalar_t__ VMCI_INVALID_ID ; 
 size_t VMCI_MAX_DG_SIZE ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  ioread8_rep (scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ roundup (uintptr_t,size_t) ; 
 int vmci_datagram_invoke_guest_handler (struct vmci_datagram*) ; 
 int vmci_event_dispatch (struct vmci_datagram*) ; 

__attribute__((used)) static void vmci_dispatch_dgs(unsigned long data)
{
	struct vmci_guest_device *vmci_dev = (struct vmci_guest_device *)data;
	u8 *dg_in_buffer = vmci_dev->data_buffer;
	struct vmci_datagram *dg;
	size_t dg_in_buffer_size = VMCI_MAX_DG_SIZE;
	size_t current_dg_in_buffer_size = PAGE_SIZE;
	size_t remaining_bytes;

	BUILD_BUG_ON(VMCI_MAX_DG_SIZE < PAGE_SIZE);

	ioread8_rep(vmci_dev->iobase + VMCI_DATA_IN_ADDR,
		    vmci_dev->data_buffer, current_dg_in_buffer_size);
	dg = (struct vmci_datagram *)dg_in_buffer;
	remaining_bytes = current_dg_in_buffer_size;

	while (dg->dst.resource != VMCI_INVALID_ID ||
	       remaining_bytes > PAGE_SIZE) {
		unsigned dg_in_size;

		/*
		 * When the input buffer spans multiple pages, a datagram can
		 * start on any page boundary in the buffer.
		 */
		if (dg->dst.resource == VMCI_INVALID_ID) {
			dg = (struct vmci_datagram *)roundup(
				(uintptr_t)dg + 1, PAGE_SIZE);
			remaining_bytes =
				(size_t)(dg_in_buffer +
					 current_dg_in_buffer_size -
					 (u8 *)dg);
			continue;
		}

		dg_in_size = VMCI_DG_SIZE_ALIGNED(dg);

		if (dg_in_size <= dg_in_buffer_size) {
			int result;

			/*
			 * If the remaining bytes in the datagram
			 * buffer doesn't contain the complete
			 * datagram, we first make sure we have enough
			 * room for it and then we read the reminder
			 * of the datagram and possibly any following
			 * datagrams.
			 */
			if (dg_in_size > remaining_bytes) {
				if (remaining_bytes !=
				    current_dg_in_buffer_size) {

					/*
					 * We move the partial
					 * datagram to the front and
					 * read the reminder of the
					 * datagram and possibly
					 * following calls into the
					 * following bytes.
					 */
					memmove(dg_in_buffer, dg_in_buffer +
						current_dg_in_buffer_size -
						remaining_bytes,
						remaining_bytes);
					dg = (struct vmci_datagram *)
					    dg_in_buffer;
				}

				if (current_dg_in_buffer_size !=
				    dg_in_buffer_size)
					current_dg_in_buffer_size =
					    dg_in_buffer_size;

				ioread8_rep(vmci_dev->iobase +
						VMCI_DATA_IN_ADDR,
					vmci_dev->data_buffer +
						remaining_bytes,
					current_dg_in_buffer_size -
						remaining_bytes);
			}

			/*
			 * We special case event datagrams from the
			 * hypervisor.
			 */
			if (dg->src.context == VMCI_HYPERVISOR_CONTEXT_ID &&
			    dg->dst.resource == VMCI_EVENT_HANDLER) {
				result = vmci_event_dispatch(dg);
			} else {
				result = vmci_datagram_invoke_guest_handler(dg);
			}
			if (result < VMCI_SUCCESS)
				dev_dbg(vmci_dev->dev,
					"Datagram with resource (ID=0x%x) failed (err=%d)\n",
					 dg->dst.resource, result);

			/* On to the next datagram. */
			dg = (struct vmci_datagram *)((u8 *)dg +
						      dg_in_size);
		} else {
			size_t bytes_to_skip;

			/*
			 * Datagram doesn't fit in datagram buffer of maximal
			 * size. We drop it.
			 */
			dev_dbg(vmci_dev->dev,
				"Failed to receive datagram (size=%u bytes)\n",
				 dg_in_size);

			bytes_to_skip = dg_in_size - remaining_bytes;
			if (current_dg_in_buffer_size != dg_in_buffer_size)
				current_dg_in_buffer_size = dg_in_buffer_size;

			for (;;) {
				ioread8_rep(vmci_dev->iobase +
						VMCI_DATA_IN_ADDR,
					vmci_dev->data_buffer,
					current_dg_in_buffer_size);
				if (bytes_to_skip <= current_dg_in_buffer_size)
					break;

				bytes_to_skip -= current_dg_in_buffer_size;
			}
			dg = (struct vmci_datagram *)(dg_in_buffer +
						      bytes_to_skip);
		}

		remaining_bytes =
		    (size_t) (dg_in_buffer + current_dg_in_buffer_size -
			      (u8 *)dg);

		if (remaining_bytes < VMCI_DG_HEADERSIZE) {
			/* Get the next batch of datagrams. */

			ioread8_rep(vmci_dev->iobase + VMCI_DATA_IN_ADDR,
				    vmci_dev->data_buffer,
				    current_dg_in_buffer_size);
			dg = (struct vmci_datagram *)dg_in_buffer;
			remaining_bytes = current_dg_in_buffer_size;
		}
	}
}