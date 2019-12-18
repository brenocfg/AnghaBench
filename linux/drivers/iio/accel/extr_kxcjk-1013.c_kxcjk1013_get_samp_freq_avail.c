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
struct kxcjk1013_data {scalar_t__ chipset; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ KXTF9 ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct kxcjk1013_data* iio_priv (struct iio_dev*) ; 
 char* kxcjk1013_samp_freq_avail ; 
 char* kxtf9_samp_freq_avail ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static ssize_t kxcjk1013_get_samp_freq_avail(struct device *dev,
					     struct device_attribute *attr,
					     char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct kxcjk1013_data *data = iio_priv(indio_dev);
	const char *str;

	if (data->chipset == KXTF9)
		str = kxtf9_samp_freq_avail;
	else
		str = kxcjk1013_samp_freq_avail;

	return sprintf(buf, "%s\n", str);
}