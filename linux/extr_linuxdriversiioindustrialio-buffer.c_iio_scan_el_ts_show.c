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
struct iio_dev {TYPE_1__* buffer; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int scan_timestamp; } ;

/* Variables and functions */
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t iio_scan_el_ts_show(struct device *dev,
				   struct device_attribute *attr,
				   char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	return sprintf(buf, "%d\n", indio_dev->buffer->scan_timestamp);
}