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
struct stk8312_data {int dready_trigger_on; TYPE_1__* client; } ;
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int STK8312_DREADY_BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct stk8312_data* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int stk8312_set_interrupts (struct stk8312_data*,int) ; 

__attribute__((used)) static int stk8312_data_rdy_trigger_set_state(struct iio_trigger *trig,
					      bool state)
{
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct stk8312_data *data = iio_priv(indio_dev);
	int ret;

	if (state)
		ret = stk8312_set_interrupts(data, STK8312_DREADY_BIT);
	else
		ret = stk8312_set_interrupts(data, 0x00);

	if (ret < 0) {
		dev_err(&data->client->dev, "failed to set trigger state\n");
		return ret;
	}

	data->dready_trigger_on = state;

	return 0;
}