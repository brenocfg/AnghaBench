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
struct kmx61_data {TYPE_1__* client; struct iio_dev* acc_indio_dev; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_ACCEL ; 
 int /*<<< orphan*/  IIO_EV_DIR_FALLING ; 
 int /*<<< orphan*/  IIO_EV_DIR_RISING ; 
 int /*<<< orphan*/  IIO_EV_TYPE_THRESH ; 
 int /*<<< orphan*/  IIO_MOD_EVENT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IIO_MOD_X ; 
 int /*<<< orphan*/  IIO_MOD_Y ; 
 int /*<<< orphan*/  IIO_MOD_Z ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KMX61_REG_CTRL1 ; 
 int KMX61_REG_CTRL1_BIT_RES ; 
 int /*<<< orphan*/  KMX61_REG_INL ; 
 int /*<<< orphan*/  KMX61_REG_INS1 ; 
 int KMX61_REG_INS1_BIT_WUFS ; 
 int /*<<< orphan*/  KMX61_REG_INS2 ; 
 int KMX61_REG_INS2_BIT_XN ; 
 int KMX61_REG_INS2_BIT_XP ; 
 int KMX61_REG_INS2_BIT_YN ; 
 int KMX61_REG_INS2_BIT_YP ; 
 int KMX61_REG_INS2_BIT_ZN ; 
 int KMX61_REG_INS2_BIT_ZP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t kmx61_event_handler(int irq, void *private)
{
	struct kmx61_data *data = private;
	struct iio_dev *indio_dev = data->acc_indio_dev;
	int ret;

	ret = i2c_smbus_read_byte_data(data->client, KMX61_REG_INS1);
	if (ret < 0) {
		dev_err(&data->client->dev, "Error reading reg_ins1\n");
		goto ack_intr;
	}

	if (ret & KMX61_REG_INS1_BIT_WUFS) {
		ret = i2c_smbus_read_byte_data(data->client, KMX61_REG_INS2);
		if (ret < 0) {
			dev_err(&data->client->dev, "Error reading reg_ins2\n");
			goto ack_intr;
		}

		if (ret & KMX61_REG_INS2_BIT_XN)
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL,
				       0,
				       IIO_MOD_X,
				       IIO_EV_TYPE_THRESH,
				       IIO_EV_DIR_FALLING),
				       0);

		if (ret & KMX61_REG_INS2_BIT_XP)
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL,
				       0,
				       IIO_MOD_X,
				       IIO_EV_TYPE_THRESH,
				       IIO_EV_DIR_RISING),
				       0);

		if (ret & KMX61_REG_INS2_BIT_YN)
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL,
				       0,
				       IIO_MOD_Y,
				       IIO_EV_TYPE_THRESH,
				       IIO_EV_DIR_FALLING),
				       0);

		if (ret & KMX61_REG_INS2_BIT_YP)
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL,
				       0,
				       IIO_MOD_Y,
				       IIO_EV_TYPE_THRESH,
				       IIO_EV_DIR_RISING),
				       0);

		if (ret & KMX61_REG_INS2_BIT_ZN)
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL,
				       0,
				       IIO_MOD_Z,
				       IIO_EV_TYPE_THRESH,
				       IIO_EV_DIR_FALLING),
				       0);

		if (ret & KMX61_REG_INS2_BIT_ZP)
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL,
				       0,
				       IIO_MOD_Z,
				       IIO_EV_TYPE_THRESH,
				       IIO_EV_DIR_RISING),
				       0);
	}

ack_intr:
	ret = i2c_smbus_read_byte_data(data->client, KMX61_REG_CTRL1);
	if (ret < 0)
		dev_err(&data->client->dev, "Error reading reg_ctrl1\n");

	ret |= KMX61_REG_CTRL1_BIT_RES;
	ret = i2c_smbus_write_byte_data(data->client, KMX61_REG_CTRL1, ret);
	if (ret < 0)
		dev_err(&data->client->dev, "Error writing reg_ctrl1\n");

	ret = i2c_smbus_read_byte_data(data->client, KMX61_REG_INL);
	if (ret < 0)
		dev_err(&data->client->dev, "Error reading reg_inl\n");

	return IRQ_HANDLED;
}