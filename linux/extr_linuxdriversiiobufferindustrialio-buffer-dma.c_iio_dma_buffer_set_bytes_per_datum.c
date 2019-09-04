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
struct iio_buffer {size_t bytes_per_datum; } ;

/* Variables and functions */

int iio_dma_buffer_set_bytes_per_datum(struct iio_buffer *buffer, size_t bpd)
{
	buffer->bytes_per_datum = bpd;

	return 0;
}