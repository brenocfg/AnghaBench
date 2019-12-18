#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {TYPE_1__* buffer; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  address; } ;
struct TYPE_3__ {int /*<<< orphan*/  scan_mask; } ;

/* Variables and functions */
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t iio_scan_el_show(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	int ret;
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);

	/* Ensure ret is 0 or 1. */
	ret = !!test_bit(to_iio_dev_attr(attr)->address,
		       indio_dev->buffer->scan_mask);

	return sprintf(buf, "%d\n", ret);
}