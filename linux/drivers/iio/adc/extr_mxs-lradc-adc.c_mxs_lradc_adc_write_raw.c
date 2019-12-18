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
struct mxs_lradc_scale {int integer; int nano; } ;
struct mxs_lradc_adc {int /*<<< orphan*/  is_divided; struct mxs_lradc_scale** scale_avail; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_SCALE 128 
 size_t MXS_LRADC_DIV_DISABLED ; 
 size_t MXS_LRADC_DIV_ENABLED ; 
 int /*<<< orphan*/  clear_bit (size_t,int /*<<< orphan*/ *) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct mxs_lradc_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxs_lradc_adc_write_raw(struct iio_dev *iio_dev,
				   const struct iio_chan_spec *chan,
				   int val, int val2, long m)
{
	struct mxs_lradc_adc *adc = iio_priv(iio_dev);
	struct mxs_lradc_scale *scale_avail =
			adc->scale_avail[chan->channel];
	int ret;

	ret = iio_device_claim_direct_mode(iio_dev);
	if (ret)
		return ret;

	switch (m) {
	case IIO_CHAN_INFO_SCALE:
		ret = -EINVAL;
		if (val == scale_avail[MXS_LRADC_DIV_DISABLED].integer &&
		    val2 == scale_avail[MXS_LRADC_DIV_DISABLED].nano) {
			/* divider by two disabled */
			clear_bit(chan->channel, &adc->is_divided);
			ret = 0;
		} else if (val == scale_avail[MXS_LRADC_DIV_ENABLED].integer &&
			   val2 == scale_avail[MXS_LRADC_DIV_ENABLED].nano) {
			/* divider by two enabled */
			set_bit(chan->channel, &adc->is_divided);
			ret = 0;
		}

		break;
	default:
		ret = -EINVAL;
		break;
	}

	iio_device_release_direct_mode(iio_dev);

	return ret;
}