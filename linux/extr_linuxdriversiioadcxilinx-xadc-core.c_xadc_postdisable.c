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
struct xadc {int dummy; } ;
struct iio_dev {int num_channels; TYPE_1__* channels; } ;
struct TYPE_2__ {int /*<<< orphan*/  scan_index; } ;

/* Variables and functions */
 unsigned long BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XADC_CONF1_SEQ_CONTINUOUS ; 
 int /*<<< orphan*/  XADC_CONF1_SEQ_MASK ; 
 int /*<<< orphan*/  XADC_REG_CONF1 ; 
 int /*<<< orphan*/  XADC_REG_SEQ (int) ; 
 struct xadc* iio_priv (struct iio_dev*) ; 
 int xadc_power_adc_b (struct xadc*,int /*<<< orphan*/ ) ; 
 int xadc_update_adc_reg (struct xadc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xadc_write_adc_reg (struct xadc*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int xadc_postdisable(struct iio_dev *indio_dev)
{
	struct xadc *xadc = iio_priv(indio_dev);
	unsigned long scan_mask;
	int ret;
	int i;

	scan_mask = 1; /* Run calibration as part of the sequence */
	for (i = 0; i < indio_dev->num_channels; i++)
		scan_mask |= BIT(indio_dev->channels[i].scan_index);

	/* Enable all channels and calibration */
	ret = xadc_write_adc_reg(xadc, XADC_REG_SEQ(0), scan_mask & 0xffff);
	if (ret)
		return ret;

	ret = xadc_write_adc_reg(xadc, XADC_REG_SEQ(1), scan_mask >> 16);
	if (ret)
		return ret;

	ret = xadc_update_adc_reg(xadc, XADC_REG_CONF1, XADC_CONF1_SEQ_MASK,
		XADC_CONF1_SEQ_CONTINUOUS);
	if (ret)
		return ret;

	return xadc_power_adc_b(xadc, XADC_CONF1_SEQ_CONTINUOUS);
}