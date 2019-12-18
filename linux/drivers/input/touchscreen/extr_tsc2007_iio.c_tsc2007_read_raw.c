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
struct tsc2007_iio {struct tsc2007* ts; } ;
struct tsc2007 {int /*<<< orphan*/  mlock; } ;
struct ts_event {void* z2; void* z1; void* x; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel; } ;

/* Variables and functions */
 int ADC_ON_12BIT ; 
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 long IIO_CHAN_INFO_RAW ; 
 int IIO_VAL_INT ; 
 int PWRDOWN ; 
 int READ_X ; 
 int READ_Y ; 
 int READ_Z1 ; 
 int READ_Z2 ; 
 int TSC2007_MEASURE_AUX ; 
 int TSC2007_MEASURE_TEMP0 ; 
 int TSC2007_MEASURE_TEMP1 ; 
 struct tsc2007_iio* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tsc2007_calculate_resistance (struct tsc2007*,struct ts_event*) ; 
 int /*<<< orphan*/  tsc2007_iio_channel ; 
 int tsc2007_is_pen_down (struct tsc2007*) ; 
 void* tsc2007_xfer (struct tsc2007*,int) ; 

__attribute__((used)) static int tsc2007_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long mask)
{
	struct tsc2007_iio *iio = iio_priv(indio_dev);
	struct tsc2007 *tsc = iio->ts;
	int adc_chan = chan->channel;
	int ret = 0;

	if (adc_chan >= ARRAY_SIZE(tsc2007_iio_channel))
		return -EINVAL;

	if (mask != IIO_CHAN_INFO_RAW)
		return -EINVAL;

	mutex_lock(&tsc->mlock);

	switch (chan->channel) {
	case 0:
		*val = tsc2007_xfer(tsc, READ_X);
		break;
	case 1:
		*val = tsc2007_xfer(tsc, READ_Y);
		break;
	case 2:
		*val = tsc2007_xfer(tsc, READ_Z1);
		break;
	case 3:
		*val = tsc2007_xfer(tsc, READ_Z2);
		break;
	case 4:
		*val = tsc2007_xfer(tsc, (ADC_ON_12BIT | TSC2007_MEASURE_AUX));
		break;
	case 5: {
		struct ts_event tc;

		tc.x = tsc2007_xfer(tsc, READ_X);
		tc.z1 = tsc2007_xfer(tsc, READ_Z1);
		tc.z2 = tsc2007_xfer(tsc, READ_Z2);
		*val = tsc2007_calculate_resistance(tsc, &tc);
		break;
	}
	case 6:
		*val = tsc2007_is_pen_down(tsc);
		break;
	case 7:
		*val = tsc2007_xfer(tsc,
				    (ADC_ON_12BIT | TSC2007_MEASURE_TEMP0));
		break;
	case 8:
		*val = tsc2007_xfer(tsc,
				    (ADC_ON_12BIT | TSC2007_MEASURE_TEMP1));
		break;
	}

	/* Prepare for next touch reading - power down ADC, enable PENIRQ */
	tsc2007_xfer(tsc, PWRDOWN);

	mutex_unlock(&tsc->mlock);

	ret = IIO_VAL_INT;

	return ret;
}