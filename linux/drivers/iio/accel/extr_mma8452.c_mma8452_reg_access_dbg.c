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
struct mma8452_data {int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int MMA8452_MAX_REG ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,unsigned int) ; 
 struct mma8452_data* iio_priv (struct iio_dev*) ; 
 int mma8452_change_config (struct mma8452_data*,unsigned int,unsigned int) ; 

__attribute__((used)) static int mma8452_reg_access_dbg(struct iio_dev *indio_dev,
				  unsigned int reg, unsigned int writeval,
				  unsigned int *readval)
{
	int ret;
	struct mma8452_data *data = iio_priv(indio_dev);

	if (reg > MMA8452_MAX_REG)
		return -EINVAL;

	if (!readval)
		return mma8452_change_config(data, reg, writeval);

	ret = i2c_smbus_read_byte_data(data->client, reg);
	if (ret < 0)
		return ret;

	*readval = ret;

	return 0;
}