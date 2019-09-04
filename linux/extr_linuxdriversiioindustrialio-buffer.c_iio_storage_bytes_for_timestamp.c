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
struct iio_dev {int /*<<< orphan*/  scan_index_timestamp; } ;

/* Variables and functions */
 unsigned int iio_storage_bytes_for_si (struct iio_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int iio_storage_bytes_for_timestamp(struct iio_dev *indio_dev)
{
	return iio_storage_bytes_for_si(indio_dev,
					indio_dev->scan_index_timestamp);
}