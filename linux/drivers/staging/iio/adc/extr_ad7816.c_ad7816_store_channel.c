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
struct iio_dev {int /*<<< orphan*/  name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7816_chip_info {unsigned long channel_id; TYPE_1__* spi_dev; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long AD7816_CS_MASK ; 
 unsigned long AD7816_CS_MAX ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned long,...) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad7816_chip_info* iio_priv (struct iio_dev*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t ad7816_store_channel(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf,
				    size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7816_chip_info *chip = iio_priv(indio_dev);
	unsigned long data;
	int ret;

	ret = kstrtoul(buf, 10, &data);
	if (ret)
		return ret;

	if (data > AD7816_CS_MAX && data != AD7816_CS_MASK) {
		dev_err(&chip->spi_dev->dev, "Invalid channel id %lu for %s.\n",
			data, indio_dev->name);
		return -EINVAL;
	} else if (strcmp(indio_dev->name, "ad7818") == 0 && data > 1) {
		dev_err(&chip->spi_dev->dev,
			"Invalid channel id %lu for ad7818.\n", data);
		return -EINVAL;
	} else if (strcmp(indio_dev->name, "ad7816") == 0 && data > 0) {
		dev_err(&chip->spi_dev->dev,
			"Invalid channel id %lu for ad7816.\n", data);
		return -EINVAL;
	}

	chip->channel_id = data;

	return len;
}