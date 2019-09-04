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
struct us5182d_data {int /*<<< orphan*/  client; int /*<<< orphan*/  upper_dark_gain; int /*<<< orphan*/  lower_dark_gain; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  US5182D_CFG1_AGAIN_DEFAULT ; 
 int /*<<< orphan*/  US5182D_REG_AUTO_HDARK_GAIN ; 
 int /*<<< orphan*/  US5182D_REG_AUTO_LDARK_GAIN ; 
 int /*<<< orphan*/  US5182D_REG_DARK_AUTO_EN ; 
 int /*<<< orphan*/  US5182D_REG_DARK_AUTO_EN_DEFAULT ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct us5182d_data* iio_priv (struct iio_dev*) ; 
 int us5182d_update_dark_th (struct us5182d_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int  us5182d_dark_gain_config(struct iio_dev *indio_dev)
{
	struct us5182d_data *data = iio_priv(indio_dev);
	int ret;

	ret = us5182d_update_dark_th(data, US5182D_CFG1_AGAIN_DEFAULT);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_byte_data(data->client,
					US5182D_REG_AUTO_LDARK_GAIN,
					data->lower_dark_gain);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_byte_data(data->client,
					US5182D_REG_AUTO_HDARK_GAIN,
					data->upper_dark_gain);
	if (ret < 0)
		return ret;

	return i2c_smbus_write_byte_data(data->client, US5182D_REG_DARK_AUTO_EN,
					 US5182D_REG_DARK_AUTO_EN_DEFAULT);
}