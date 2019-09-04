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
struct kmx61_data {int odr_bits; int /*<<< orphan*/  wake_duration; int /*<<< orphan*/  wake_thresh; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int KMX61_ACC ; 
 int KMX61_CHIP_ID ; 
 int /*<<< orphan*/  KMX61_DEFAULT_WAKE_DURATION ; 
 int /*<<< orphan*/  KMX61_DEFAULT_WAKE_THRESH ; 
 int KMX61_MAG ; 
 int /*<<< orphan*/  KMX61_RANGE_4G ; 
 int /*<<< orphan*/  KMX61_REG_ODCNTL ; 
 int /*<<< orphan*/  KMX61_REG_WHO_AM_I ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int kmx61_get_odr (struct kmx61_data*,int*,int*,int) ; 
 int kmx61_set_mode (struct kmx61_data*,int /*<<< orphan*/ ,int,int) ; 
 int kmx61_set_range (struct kmx61_data*,int /*<<< orphan*/ ) ; 
 int kmx61_set_wake_up_odr (struct kmx61_data*,int,int) ; 

__attribute__((used)) static int kmx61_chip_init(struct kmx61_data *data)
{
	int ret, val, val2;

	ret = i2c_smbus_read_byte_data(data->client, KMX61_REG_WHO_AM_I);
	if (ret < 0) {
		dev_err(&data->client->dev, "Error reading who_am_i\n");
		return ret;
	}

	if (ret != KMX61_CHIP_ID) {
		dev_err(&data->client->dev,
			"Wrong chip id, got %x expected %x\n",
			 ret, KMX61_CHIP_ID);
		return -EINVAL;
	}

	/* set accel 12bit, 4g range */
	ret = kmx61_set_range(data, KMX61_RANGE_4G);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_read_byte_data(data->client, KMX61_REG_ODCNTL);
	if (ret < 0) {
		dev_err(&data->client->dev, "Error reading reg_odcntl\n");
		return ret;
	}
	data->odr_bits = ret;

	/*
	 * set output data rate for wake up (motion detection) function
	 * to match data rate for accelerometer sampling
	 */
	ret = kmx61_get_odr(data, &val, &val2, KMX61_ACC);
	if (ret < 0)
		return ret;

	ret = kmx61_set_wake_up_odr(data, val, val2);
	if (ret < 0)
		return ret;

	/* set acc/magn to OPERATION mode */
	ret = kmx61_set_mode(data, 0, KMX61_ACC | KMX61_MAG, true);
	if (ret < 0)
		return ret;

	data->wake_thresh = KMX61_DEFAULT_WAKE_THRESH;
	data->wake_duration = KMX61_DEFAULT_WAKE_DURATION;

	return 0;
}