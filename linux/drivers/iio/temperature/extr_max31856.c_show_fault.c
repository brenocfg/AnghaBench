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
struct max31856_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX31856_SR_REG ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct max31856_data* iio_priv (struct iio_dev*) ; 
 int max31856_read (struct max31856_data*,int /*<<< orphan*/ ,int*,int) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_fault(struct device *dev, u8 faultbit, char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct max31856_data *data = iio_priv(indio_dev);
	u8 reg_val;
	int ret;
	bool fault;

	ret = max31856_read(data, MAX31856_SR_REG, &reg_val, 1);
	if (ret)
		return ret;

	fault = reg_val & faultbit;

	return sprintf(buf, "%d\n", fault);
}