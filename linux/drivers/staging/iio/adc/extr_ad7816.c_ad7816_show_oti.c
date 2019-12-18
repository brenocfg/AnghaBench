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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7816_chip_info {size_t channel_id; int* oti_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int AD7816_BOUND_VALUE_BASE ; 
 int AD7816_BOUND_VALUE_MIN ; 
 size_t AD7816_CS_MAX ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad7816_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t ad7816_show_oti(struct device *dev,
			       struct device_attribute *attr,
			       char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7816_chip_info *chip = iio_priv(indio_dev);
	int value;

	if (chip->channel_id > AD7816_CS_MAX) {
		dev_err(dev, "Invalid oti channel id %d.\n", chip->channel_id);
		return -EINVAL;
	} else if (chip->channel_id == 0) {
		value = AD7816_BOUND_VALUE_MIN +
			(chip->oti_data[chip->channel_id] -
			AD7816_BOUND_VALUE_BASE);
		return sprintf(buf, "%d\n", value);
	}
	return sprintf(buf, "%u\n", chip->oti_data[chip->channel_id]);
}