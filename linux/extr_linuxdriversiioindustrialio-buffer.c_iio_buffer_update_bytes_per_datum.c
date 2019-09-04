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
struct iio_dev {int dummy; } ;
struct iio_buffer {TYPE_1__* access; int /*<<< orphan*/  scan_timestamp; int /*<<< orphan*/  scan_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_bytes_per_datum ) (struct iio_buffer*,unsigned int) ;} ;

/* Variables and functions */
 unsigned int iio_compute_scan_bytes (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct iio_buffer*,unsigned int) ; 

__attribute__((used)) static void iio_buffer_update_bytes_per_datum(struct iio_dev *indio_dev,
	struct iio_buffer *buffer)
{
	unsigned int bytes;

	if (!buffer->access->set_bytes_per_datum)
		return;

	bytes = iio_compute_scan_bytes(indio_dev, buffer->scan_mask,
		buffer->scan_timestamp);

	buffer->access->set_bytes_per_datum(buffer, bytes);
}