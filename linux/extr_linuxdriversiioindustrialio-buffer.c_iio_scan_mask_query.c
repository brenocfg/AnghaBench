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
struct iio_dev {int masklength; } ;
struct iio_buffer {int /*<<< orphan*/  scan_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iio_scan_mask_query(struct iio_dev *indio_dev,
			       struct iio_buffer *buffer, int bit)
{
	if (bit > indio_dev->masklength)
		return -EINVAL;

	if (!buffer->scan_mask)
		return 0;

	/* Ensure return value is 0 or 1. */
	return !!test_bit(bit, buffer->scan_mask);
}