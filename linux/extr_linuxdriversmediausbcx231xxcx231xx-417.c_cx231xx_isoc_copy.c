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
typedef  size_t u32 ;
struct urb {size_t number_of_packets; unsigned char* transfer_buffer; TYPE_1__* iso_frame_desc; struct cx231xx_dmaqueue* context; } ;
struct cx231xx_dmaqueue {scalar_t__ left_data_count; unsigned char* p_left_data; size_t mpeg_buffer_completed; } ;
struct cx231xx {int dummy; } ;
struct TYPE_2__ {int offset; size_t actual_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_copy (struct cx231xx*,unsigned char*,size_t,struct urb*,struct cx231xx_dmaqueue*) ; 

__attribute__((used)) static int cx231xx_isoc_copy(struct cx231xx *dev, struct urb *urb)
{
	struct cx231xx_dmaqueue *dma_q = urb->context;
	unsigned char *p_buffer;
	u32 buffer_size = 0;
	u32 i = 0;

	for (i = 0; i < urb->number_of_packets; i++) {
		if (dma_q->left_data_count > 0) {
			buffer_copy(dev, dma_q->p_left_data,
				    dma_q->left_data_count, urb, dma_q);
			dma_q->mpeg_buffer_completed = dma_q->left_data_count;
			dma_q->left_data_count = 0;
		}

		p_buffer = urb->transfer_buffer +
				urb->iso_frame_desc[i].offset;
		buffer_size = urb->iso_frame_desc[i].actual_length;

		if (buffer_size > 0)
			buffer_copy(dev, p_buffer, buffer_size, urb, dma_q);
	}

	return 0;
}