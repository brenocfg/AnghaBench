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
struct iio_dev {int dummy; } ;
struct hid_sensor_common {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int hid_sensor_get_report_latency (struct hid_sensor_common*) ; 
 struct hid_sensor_common* iio_device_get_drvdata (struct iio_dev*) ; 
 int sprintf (char*,char*,int,int) ; 

__attribute__((used)) static ssize_t _hid_sensor_get_report_latency(struct device *dev,
					      struct device_attribute *attr,
					      char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct hid_sensor_common *attrb = iio_device_get_drvdata(indio_dev);
	int latency;

	latency = hid_sensor_get_report_latency(attrb);
	if (latency < 0)
		return latency;

	return sprintf(buf, "%d.%06u\n", latency / 1000, (latency % 1000) * 1000);
}