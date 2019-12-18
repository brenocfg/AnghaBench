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
struct iio_dev {int dummy; } ;
struct gp2ap020a00f_data {scalar_t__* thresh_val; TYPE_1__* client; } ;
typedef  enum gp2ap020a00f_cmd { ____Placeholder_gp2ap020a00f_cmd } gp2ap020a00f_cmd ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int GP2AP020A00F_CMD_PROX_HIGH_EV_DIS ; 
 int GP2AP020A00F_CMD_PROX_HIGH_EV_EN ; 
 int GP2AP020A00F_CMD_PROX_LOW_EV_DIS ; 
 int GP2AP020A00F_CMD_PROX_LOW_EV_EN ; 
 size_t GP2AP020A00F_THRESH_PH ; 
 size_t GP2AP020A00F_THRESH_PL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct iio_dev*) ; 
 int gp2ap020a00f_exec_cmd (struct gp2ap020a00f_data*,int) ; 
 int /*<<< orphan*/  gp2ap020a00f_prox_sensing_handler ; 
 int /*<<< orphan*/  gp2ap020a00f_thresh_event_handler ; 
 struct gp2ap020a00f_data* iio_priv (struct iio_dev*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,struct iio_dev*) ; 

__attribute__((used)) static int gp2ap020a00f_write_prox_event_config(struct iio_dev *indio_dev,
						int state)
{
	struct gp2ap020a00f_data *data = iio_priv(indio_dev);
	enum gp2ap020a00f_cmd cmd_high_ev, cmd_low_ev;
	int err;

	cmd_high_ev = state ? GP2AP020A00F_CMD_PROX_HIGH_EV_EN :
			      GP2AP020A00F_CMD_PROX_HIGH_EV_DIS;
	cmd_low_ev = state ? GP2AP020A00F_CMD_PROX_LOW_EV_EN :
			     GP2AP020A00F_CMD_PROX_LOW_EV_DIS;

	/*
	 * In order to enable proximity detection feature in the device
	 * both high and low threshold registers have to be written
	 * with different values, greater than zero.
	 */
	if (state) {
		if (data->thresh_val[GP2AP020A00F_THRESH_PL] == 0)
			return -EINVAL;

		if (data->thresh_val[GP2AP020A00F_THRESH_PH] == 0)
			return -EINVAL;
	}

	err = gp2ap020a00f_exec_cmd(data, cmd_high_ev);
	if (err < 0)
		return err;

	err = gp2ap020a00f_exec_cmd(data, cmd_low_ev);
	if (err < 0)
		return err;

	free_irq(data->client->irq, indio_dev);

	if (state)
		err = request_threaded_irq(data->client->irq, NULL,
					   &gp2ap020a00f_prox_sensing_handler,
					   IRQF_TRIGGER_RISING |
					   IRQF_TRIGGER_FALLING |
					   IRQF_ONESHOT,
					   "gp2ap020a00f_prox_sensing",
					   indio_dev);
	else {
		err = request_threaded_irq(data->client->irq, NULL,
					   &gp2ap020a00f_thresh_event_handler,
					   IRQF_TRIGGER_FALLING |
					   IRQF_ONESHOT,
					   "gp2ap020a00f_thresh_event",
					   indio_dev);
	}

	return err;
}