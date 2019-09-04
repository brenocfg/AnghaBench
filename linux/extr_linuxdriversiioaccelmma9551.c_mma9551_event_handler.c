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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mma9551_data {int* irqs; int /*<<< orphan*/  mutex; TYPE_1__* client; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_EV_DIR_RISING ; 
 int /*<<< orphan*/  IIO_EV_TYPE_ROC ; 
 int /*<<< orphan*/  IIO_INCLI ; 
 int /*<<< orphan*/  IIO_MOD_EVENT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MMA9551_APPID_TILT ; 
 int /*<<< orphan*/  MMA9551_TILT_XY_ANG_REG ; 
 int /*<<< orphan*/  MMA9551_TILT_XZ_ANG_REG ; 
 int /*<<< orphan*/  MMA9551_TILT_YZ_ANG_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct mma9551_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mma9551_read_status_byte (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  mma9551_x 130 
#define  mma9551_y 129 
#define  mma9551_z 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mma9551_event_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct mma9551_data *data = iio_priv(indio_dev);
	int i, ret, mma_axis = -1;
	u16 reg;
	u8 val;

	mutex_lock(&data->mutex);

	for (i = 0; i < 3; i++)
		if (irq == data->irqs[i]) {
			mma_axis = i;
			break;
		}

	if (mma_axis == -1) {
		/* IRQ was triggered on 4th line, which we don't use. */
		dev_warn(&data->client->dev,
			 "irq triggered on unused line %d\n", data->irqs[3]);
		goto out;
	}

	switch (mma_axis) {
	case mma9551_x:
		reg = MMA9551_TILT_YZ_ANG_REG;
		break;
	case mma9551_y:
		reg = MMA9551_TILT_XZ_ANG_REG;
		break;
	case mma9551_z:
		reg = MMA9551_TILT_XY_ANG_REG;
		break;
	}

	/*
	 * Read the angle even though we don't use it, otherwise we
	 * won't get any further interrupts.
	 */
	ret = mma9551_read_status_byte(data->client, MMA9551_APPID_TILT,
				       reg, &val);
	if (ret < 0) {
		dev_err(&data->client->dev,
			"error %d reading tilt register in IRQ\n", ret);
		goto out;
	}

	iio_push_event(indio_dev,
		       IIO_MOD_EVENT_CODE(IIO_INCLI, 0, (mma_axis + 1),
					  IIO_EV_TYPE_ROC, IIO_EV_DIR_RISING),
		       iio_get_time_ns(indio_dev));

out:
	mutex_unlock(&data->mutex);

	return IRQ_HANDLED;
}