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
struct urb {int transfer_buffer_length; int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/ **** transfer_buffer; scalar_t__ sg; scalar_t__ num_sgs; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int DWC2_USB_DMA_ALIGN ; 
 int ENOMEM ; 
 void* PTR_ALIGN (void*,int) ; 
 int /*<<< orphan*/  URB_ALIGNED_TEMP_BUFFER ; 
 int dma_get_cache_alignment () ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ***,int) ; 
 scalar_t__ usb_urb_dir_out (struct urb*) ; 

__attribute__((used)) static int dwc2_alloc_dma_aligned_buffer(struct urb *urb, gfp_t mem_flags)
{
	void *kmalloc_ptr;
	size_t kmalloc_size;

	if (urb->num_sgs || urb->sg ||
	    urb->transfer_buffer_length == 0 ||
	    !((uintptr_t)urb->transfer_buffer & (DWC2_USB_DMA_ALIGN - 1)))
		return 0;

	/*
	 * Allocate a buffer with enough padding for original transfer_buffer
	 * pointer. This allocation is guaranteed to be aligned properly for
	 * DMA
	 */
	kmalloc_size = urb->transfer_buffer_length +
		(dma_get_cache_alignment() - 1) +
		sizeof(urb->transfer_buffer);

	kmalloc_ptr = kmalloc(kmalloc_size, mem_flags);
	if (!kmalloc_ptr)
		return -ENOMEM;

	/*
	 * Position value of original urb->transfer_buffer pointer to the end
	 * of allocation for later referencing
	 */
	memcpy(PTR_ALIGN(kmalloc_ptr + urb->transfer_buffer_length,
			 dma_get_cache_alignment()),
	       &urb->transfer_buffer, sizeof(urb->transfer_buffer));

	if (usb_urb_dir_out(urb))
		memcpy(kmalloc_ptr, urb->transfer_buffer,
		       urb->transfer_buffer_length);
	urb->transfer_buffer = kmalloc_ptr;

	urb->transfer_flags |= URB_ALIGNED_TEMP_BUFFER;

	return 0;
}