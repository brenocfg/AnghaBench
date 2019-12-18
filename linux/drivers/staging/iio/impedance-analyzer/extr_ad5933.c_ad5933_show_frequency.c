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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned long long u64 ;
struct iio_dev_attr {int /*<<< orphan*/  address; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad5933_state {int mclk_hz; int /*<<< orphan*/  client; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int ad5933_i2c_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int /*<<< orphan*/ ) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct ad5933_state* iio_priv (struct iio_dev*) ; 
 int sprintf (char*,char*,int) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ad5933_show_frequency(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad5933_state *st = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	int ret;
	unsigned long long freqreg;
	union {
		__be32 d32;
		u8 d8[4];
	} dat;

	ret = iio_device_claim_direct_mode(indio_dev);
	if (ret)
		return ret;
	ret = ad5933_i2c_read(st->client, this_attr->address, 3, &dat.d8[1]);
	iio_device_release_direct_mode(indio_dev);
	if (ret < 0)
		return ret;

	freqreg = be32_to_cpu(dat.d32) & 0xFFFFFF;

	freqreg = (u64)freqreg * (u64)(st->mclk_hz / 4);
	do_div(freqreg, BIT(27));

	return sprintf(buf, "%d\n", (int)freqreg);
}