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
struct urb {int transfer_flags; size_t transfer_buffer_length; size_t actual_length; void* transfer_buffer; int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 void* PTR_ALIGN (void*,int /*<<< orphan*/ ) ; 
 int URB_ALIGNED_TEMP_BUFFER ; 
 int /*<<< orphan*/  dma_get_cache_alignment () ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 scalar_t__ usb_pipeisoc (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_urb_dir_in (struct urb*) ; 

__attribute__((used)) static void dwc2_free_dma_aligned_buffer(struct urb *urb)
{
	void *stored_xfer_buffer;
	size_t length;

	if (!(urb->transfer_flags & URB_ALIGNED_TEMP_BUFFER))
		return;

	/* Restore urb->transfer_buffer from the end of the allocated area */
	memcpy(&stored_xfer_buffer,
	       PTR_ALIGN(urb->transfer_buffer + urb->transfer_buffer_length,
			 dma_get_cache_alignment()),
	       sizeof(urb->transfer_buffer));

	if (usb_urb_dir_in(urb)) {
		if (usb_pipeisoc(urb->pipe))
			length = urb->transfer_buffer_length;
		else
			length = urb->actual_length;

		memcpy(stored_xfer_buffer, urb->transfer_buffer, length);
	}
	kfree(urb->transfer_buffer);
	urb->transfer_buffer = stored_xfer_buffer;

	urb->transfer_flags &= ~URB_ALIGNED_TEMP_BUFFER;
}