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
struct iio_dev {struct iio_buffer* buffer; } ;
struct iio_buffer {int watermark; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t iio_buffer_show_watermark(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct iio_buffer *buffer = indio_dev->buffer;

	return sprintf(buf, "%u\n", buffer->watermark);
}