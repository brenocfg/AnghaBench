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
struct urb {int transfer_flags; scalar_t__ transfer_buffer; scalar_t__ transfer_dma; scalar_t__ transfer_buffer_length; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int URB_NO_TRANSFER_DMA_MAP ; 
 unsigned long buffer_offset (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static void simple_free_urb(struct urb *urb)
{
	unsigned long offset = buffer_offset(urb->transfer_buffer);

	if (urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP)
		usb_free_coherent(
			urb->dev,
			urb->transfer_buffer_length + offset,
			urb->transfer_buffer - offset,
			urb->transfer_dma - offset);
	else
		kfree(urb->transfer_buffer - offset);
	usb_free_urb(urb);
}