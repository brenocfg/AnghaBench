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
struct twl4030_madc_request {int active; int raw; int do_avg; int* rbuf; int /*<<< orphan*/  type; int /*<<< orphan*/  channels; int /*<<< orphan*/  method; } ;
struct twl4030_madc_data {scalar_t__ use_second_irq; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 
 long IIO_CHAN_INFO_AVERAGE_RAW ; 
 long IIO_CHAN_INFO_PROCESSED ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  TWL4030_MADC_SW1 ; 
 int /*<<< orphan*/  TWL4030_MADC_SW2 ; 
 int /*<<< orphan*/  TWL4030_MADC_WAIT ; 
 struct twl4030_madc_data* iio_priv (struct iio_dev*) ; 
 int twl4030_madc_conversion (struct twl4030_madc_request*) ; 

__attribute__((used)) static int twl4030_madc_read(struct iio_dev *iio_dev,
			     const struct iio_chan_spec *chan,
			     int *val, int *val2, long mask)
{
	struct twl4030_madc_data *madc = iio_priv(iio_dev);
	struct twl4030_madc_request req;
	int ret;

	req.method = madc->use_second_irq ? TWL4030_MADC_SW2 : TWL4030_MADC_SW1;

	req.channels = BIT(chan->channel);
	req.active = false;
	req.type = TWL4030_MADC_WAIT;
	req.raw = !(mask == IIO_CHAN_INFO_PROCESSED);
	req.do_avg = (mask == IIO_CHAN_INFO_AVERAGE_RAW);

	ret = twl4030_madc_conversion(&req);
	if (ret < 0)
		return ret;

	*val = req.rbuf[chan->channel];

	return IIO_VAL_INT;
}