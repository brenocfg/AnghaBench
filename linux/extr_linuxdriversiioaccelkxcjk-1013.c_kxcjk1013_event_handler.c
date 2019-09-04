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
struct kxcjk1013_data {scalar_t__ chipset; TYPE_1__* client; scalar_t__ dready_trigger_on; int /*<<< orphan*/  timestamp; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_ACCEL ; 
 int /*<<< orphan*/  IIO_EV_DIR_RISING ; 
 int /*<<< orphan*/  IIO_EV_TYPE_THRESH ; 
 int /*<<< orphan*/  IIO_MOD_EVENT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IIO_MOD_X_AND_Y_AND_Z ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KXCJK1013_REG_INT_REL ; 
 int /*<<< orphan*/  KXCJK1013_REG_INT_SRC1 ; 
 int KXCJK1013_REG_INT_SRC1_BIT_WUFS ; 
 scalar_t__ KXTF9 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct kxcjk1013_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxcjk1013_report_motion_event (struct iio_dev*) ; 

__attribute__((used)) static irqreturn_t kxcjk1013_event_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct kxcjk1013_data *data = iio_priv(indio_dev);
	int ret;

	ret = i2c_smbus_read_byte_data(data->client, KXCJK1013_REG_INT_SRC1);
	if (ret < 0) {
		dev_err(&data->client->dev, "Error reading reg_int_src1\n");
		goto ack_intr;
	}

	if (ret & KXCJK1013_REG_INT_SRC1_BIT_WUFS) {
		if (data->chipset == KXTF9)
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL,
				       0,
				       IIO_MOD_X_AND_Y_AND_Z,
				       IIO_EV_TYPE_THRESH,
				       IIO_EV_DIR_RISING),
				       data->timestamp);
		else
			kxcjk1013_report_motion_event(indio_dev);
	}

ack_intr:
	if (data->dready_trigger_on)
		return IRQ_HANDLED;

	ret = i2c_smbus_read_byte_data(data->client, KXCJK1013_REG_INT_REL);
	if (ret < 0)
		dev_err(&data->client->dev, "Error reading reg_int_rel\n");

	return IRQ_HANDLED;
}