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
struct gp2ap020a00f_data {int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  GP2AP020A00F_OP_REG ; 
 unsigned int GP2AP020A00F_PROX_DETECT ; 
 int /*<<< orphan*/  GP2AP020A00F_SCAN_MODE_PROXIMITY ; 
 int /*<<< orphan*/  IIO_EV_DIR_FALLING ; 
 int /*<<< orphan*/  IIO_EV_DIR_RISING ; 
 int /*<<< orphan*/  IIO_EV_TYPE_ROC ; 
 int /*<<< orphan*/  IIO_PROXIMITY ; 
 int /*<<< orphan*/  IIO_UNMOD_EVENT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ gp2ap020a00f_prox_detect_enabled (struct gp2ap020a00f_data*) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct gp2ap020a00f_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static irqreturn_t gp2ap020a00f_prox_sensing_handler(int irq, void *data)
{
	struct iio_dev *indio_dev = data;
	struct gp2ap020a00f_data *priv = iio_priv(indio_dev);
	unsigned int op_reg_val;
	int ret;

	/* Read interrupt flags */
	ret = regmap_read(priv->regmap, GP2AP020A00F_OP_REG, &op_reg_val);
	if (ret < 0)
		return IRQ_HANDLED;

	if (gp2ap020a00f_prox_detect_enabled(priv)) {
		if (op_reg_val & GP2AP020A00F_PROX_DETECT) {
			iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(
				    IIO_PROXIMITY,
				    GP2AP020A00F_SCAN_MODE_PROXIMITY,
				    IIO_EV_TYPE_ROC,
				    IIO_EV_DIR_RISING),
			       iio_get_time_ns(indio_dev));
		} else {
			iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(
				    IIO_PROXIMITY,
				    GP2AP020A00F_SCAN_MODE_PROXIMITY,
				    IIO_EV_TYPE_ROC,
				    IIO_EV_DIR_FALLING),
			       iio_get_time_ns(indio_dev));
		}
	}

	return IRQ_HANDLED;
}