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
struct iio_buffer {unsigned int length; unsigned int watermark; } ;

/* Variables and functions */

int iio_dma_buffer_set_length(struct iio_buffer *buffer, unsigned int length)
{
	/* Avoid an invalid state */
	if (length < 2)
		length = 2;
	buffer->length = length;
	buffer->watermark = length / 2;

	return 0;
}