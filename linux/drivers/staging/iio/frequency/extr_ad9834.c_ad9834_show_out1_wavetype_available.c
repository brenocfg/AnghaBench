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
struct ad9834_state {int control; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int AD9834_MODE ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad9834_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static
ssize_t ad9834_show_out1_wavetype_available(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad9834_state *st = iio_priv(indio_dev);
	char *str;

	if (st->control & AD9834_MODE)
		str = "";
	else
		str = "square";

	return sprintf(buf, "%s\n", str);
}