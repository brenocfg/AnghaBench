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
typedef  int /*<<< orphan*/  u32 ;
struct urb {int transfer_flags; int transfer_buffer_length; int /*<<< orphan*/  transfer_buffer; scalar_t__ sg; scalar_t__ num_sgs; } ;
struct octeon_temp_buffer {int /*<<< orphan*/  data; int /*<<< orphan*/  orig_buffer; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ ALIGN (int,int) ; 
 int ENOMEM ; 
 int URB_ALIGNED_TEMP_BUFFER ; 
 int URB_NO_TRANSFER_DMA_MAP ; 
 struct octeon_temp_buffer* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ usb_urb_dir_out (struct urb*) ; 

__attribute__((used)) static int octeon_alloc_temp_buffer(struct urb *urb, gfp_t mem_flags)
{
	struct octeon_temp_buffer *temp;

	if (urb->num_sgs || urb->sg ||
	    (urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP) ||
	    !(urb->transfer_buffer_length % sizeof(u32)))
		return 0;

	temp = kmalloc(ALIGN(urb->transfer_buffer_length, sizeof(u32)) +
		       sizeof(*temp), mem_flags);
	if (!temp)
		return -ENOMEM;

	temp->orig_buffer = urb->transfer_buffer;
	if (usb_urb_dir_out(urb))
		memcpy(temp->data, urb->transfer_buffer,
		       urb->transfer_buffer_length);
	urb->transfer_buffer = temp->data;
	urb->transfer_flags |= URB_ALIGNED_TEMP_BUFFER;

	return 0;
}