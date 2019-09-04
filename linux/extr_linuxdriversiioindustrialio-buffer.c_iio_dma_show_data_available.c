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
struct iio_dev {int /*<<< orphan*/  buffer; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 size_t iio_buffer_data_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,size_t) ; 

__attribute__((used)) static ssize_t iio_dma_show_data_available(struct device *dev,
						struct device_attribute *attr,
						char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	size_t bytes;

	bytes = iio_buffer_data_available(indio_dev->buffer);

	return sprintf(buf, "%zu\n", bytes);
}