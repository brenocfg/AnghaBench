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
typedef  int uint16_t ;
struct xadc {unsigned int alarm_mask; int /*<<< orphan*/  mutex; TYPE_1__* ops; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_alarm ) (struct xadc*,unsigned int) ;} ;

/* Variables and functions */
 int XADC_CONF1_ALARM_MASK ; 
 int /*<<< orphan*/  XADC_REG_CONF1 ; 
 int _xadc_read_adc_reg (struct xadc*,int /*<<< orphan*/ ,int*) ; 
 int _xadc_write_adc_reg (struct xadc*,int /*<<< orphan*/ ,int) ; 
 struct xadc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct xadc*,unsigned int) ; 
 unsigned int xadc_get_alarm_mask (struct iio_chan_spec const*) ; 

int xadc_write_event_config(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_direction dir, int state)
{
	unsigned int alarm = xadc_get_alarm_mask(chan);
	struct xadc *xadc = iio_priv(indio_dev);
	uint16_t cfg, old_cfg;
	int ret;

	mutex_lock(&xadc->mutex);

	if (state)
		xadc->alarm_mask |= alarm;
	else
		xadc->alarm_mask &= ~alarm;

	xadc->ops->update_alarm(xadc, xadc->alarm_mask);

	ret = _xadc_read_adc_reg(xadc, XADC_REG_CONF1, &cfg);
	if (ret)
		goto err_out;

	old_cfg = cfg;
	cfg |= XADC_CONF1_ALARM_MASK;
	cfg &= ~((xadc->alarm_mask & 0xf0) << 4); /* bram, pint, paux, ddr */
	cfg &= ~((xadc->alarm_mask & 0x08) >> 3); /* ot */
	cfg &= ~((xadc->alarm_mask & 0x07) << 1); /* temp, vccint, vccaux */
	if (old_cfg != cfg)
		ret = _xadc_write_adc_reg(xadc, XADC_REG_CONF1, cfg);

err_out:
	mutex_unlock(&xadc->mutex);

	return ret;
}