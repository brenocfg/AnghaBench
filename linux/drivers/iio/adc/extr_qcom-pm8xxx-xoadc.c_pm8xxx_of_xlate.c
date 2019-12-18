#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct pm8xxx_xoadc {unsigned int nchans; TYPE_2__* chans; } ;
struct of_phandle_args {int args_count; scalar_t__* args; int /*<<< orphan*/  np; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__* hwchan; } ;
struct TYPE_3__ {scalar_t__ pre_scale_mux; scalar_t__ amux_channel; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 struct pm8xxx_xoadc* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int pm8xxx_of_xlate(struct iio_dev *indio_dev,
			   const struct of_phandle_args *iiospec)
{
	struct pm8xxx_xoadc *adc = iio_priv(indio_dev);
	u8 pre_scale_mux;
	u8 amux_channel;
	unsigned int i;

	/*
	 * First cell is prescaler or premux, second cell is analog
	 * mux.
	 */
	if (iiospec->args_count != 2) {
		dev_err(&indio_dev->dev, "wrong number of arguments for %pOFn need 2 got %d\n",
			iiospec->np,
			iiospec->args_count);
		return -EINVAL;
	}
	pre_scale_mux = (u8)iiospec->args[0];
	amux_channel = (u8)iiospec->args[1];
	dev_dbg(&indio_dev->dev, "pre scale/mux: %02x, amux: %02x\n",
		pre_scale_mux, amux_channel);

	/* We need to match exactly on the prescale/premux and channel */
	for (i = 0; i < adc->nchans; i++)
		if (adc->chans[i].hwchan->pre_scale_mux == pre_scale_mux &&
		    adc->chans[i].hwchan->amux_channel == amux_channel)
			return i;

	return -EINVAL;
}