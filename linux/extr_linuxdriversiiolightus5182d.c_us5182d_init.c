#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct us5182d_data {int als_enabled; int px_enabled; int /*<<< orphan*/  power_mode; int /*<<< orphan*/  default_continuous; int /*<<< orphan*/  client; int /*<<< orphan*/  px_high_th; int /*<<< orphan*/  px_low_th; scalar_t__ opmode; } ;
struct iio_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  US5182D_CFG0_SHUTDOWN_EN ; 
 int /*<<< orphan*/  US5182D_CONTINUOUS ; 
 int /*<<< orphan*/  US5182D_ONESHOT ; 
 int /*<<< orphan*/  US5182D_REG_PXH_TH_DEFAULT ; 
 int /*<<< orphan*/  US5182D_REG_PXL_TH_DEFAULT ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct us5182d_data* iio_priv (struct iio_dev*) ; 
 TYPE_1__* us5182d_regvals ; 
 int us5182d_reset (struct iio_dev*) ; 
 int us5182d_shutdown_en (struct us5182d_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int us5182d_init(struct iio_dev *indio_dev)
{
	struct us5182d_data *data = iio_priv(indio_dev);
	int i, ret;

	ret = us5182d_reset(indio_dev);
	if (ret < 0)
		return ret;

	data->opmode = 0;
	data->power_mode = US5182D_CONTINUOUS;
	data->px_low_th = US5182D_REG_PXL_TH_DEFAULT;
	data->px_high_th = US5182D_REG_PXH_TH_DEFAULT;

	for (i = 0; i < ARRAY_SIZE(us5182d_regvals); i++) {
		ret = i2c_smbus_write_byte_data(data->client,
						us5182d_regvals[i].reg,
						us5182d_regvals[i].val);
		if (ret < 0)
			return ret;
	}

	data->als_enabled = true;
	data->px_enabled = true;

	if (!data->default_continuous) {
		ret = us5182d_shutdown_en(data, US5182D_CFG0_SHUTDOWN_EN);
		if (ret < 0)
			return ret;
		data->power_mode = US5182D_ONESHOT;
	}

	return ret;
}