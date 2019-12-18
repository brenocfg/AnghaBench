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
struct mxs_lradc_adc {TYPE_1__** scale_avail; } ;
struct iio_dev_attr {int address; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int integer; int nano; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct mxs_lradc_adc* iio_priv (struct iio_dev*) ; 
 scalar_t__ sprintf (char*,char*,...) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t mxs_lradc_adc_show_scale_avail(struct device *dev,
						 struct device_attribute *attr,
						 char *buf)
{
	struct iio_dev *iio = dev_to_iio_dev(dev);
	struct mxs_lradc_adc *adc = iio_priv(iio);
	struct iio_dev_attr *iio_attr = to_iio_dev_attr(attr);
	int i, ch, len = 0;

	ch = iio_attr->address;
	for (i = 0; i < ARRAY_SIZE(adc->scale_avail[ch]); i++)
		len += sprintf(buf + len, "%u.%09u ",
			       adc->scale_avail[ch][i].integer,
			       adc->scale_avail[ch][i].nano);

	len += sprintf(buf + len, "\n");

	return len;
}