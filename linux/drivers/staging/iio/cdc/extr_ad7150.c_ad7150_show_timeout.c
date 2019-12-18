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
typedef  int u8 ;
struct iio_dev_attr {int /*<<< orphan*/  address; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7150_chip_info {int** mag_timeout; int** thresh_timeout; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int IIO_EVENT_CODE_EXTRACT_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ IIO_EVENT_CODE_EXTRACT_DIR (int /*<<< orphan*/ ) ; 
 int IIO_EVENT_CODE_EXTRACT_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ IIO_EV_DIR_RISING ; 
#define  IIO_EV_TYPE_MAG_ADAPTIVE 129 
#define  IIO_EV_TYPE_THRESH_ADAPTIVE 128 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad7150_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ad7150_show_timeout(struct device *dev,
				   struct device_attribute *attr,
				   char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7150_chip_info *chip = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	u8 value;

	/* use the event code for consistency reasons */
	int chan = IIO_EVENT_CODE_EXTRACT_CHAN(this_attr->address);
	int rising = (IIO_EVENT_CODE_EXTRACT_DIR(this_attr->address)
		      == IIO_EV_DIR_RISING) ? 1 : 0;

	switch (IIO_EVENT_CODE_EXTRACT_TYPE(this_attr->address)) {
	case IIO_EV_TYPE_MAG_ADAPTIVE:
		value = chip->mag_timeout[rising][chan];
		break;
	case IIO_EV_TYPE_THRESH_ADAPTIVE:
		value = chip->thresh_timeout[rising][chan];
		break;
	default:
		return -EINVAL;
	}

	return sprintf(buf, "%d\n", value);
}