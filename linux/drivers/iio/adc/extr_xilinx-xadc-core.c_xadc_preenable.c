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
struct xadc {int dummy; } ;
struct iio_dev {unsigned long* active_scan_mask; } ;

/* Variables and functions */
 int XADC_CONF1_SEQ_DEFAULT ; 
 int /*<<< orphan*/  XADC_CONF1_SEQ_MASK ; 
 int /*<<< orphan*/  XADC_REG_CONF1 ; 
 int /*<<< orphan*/  XADC_REG_SEQ (int) ; 
 struct xadc* iio_priv (struct iio_dev*) ; 
 int xadc_get_seq_mode (struct xadc*,unsigned long) ; 
 int /*<<< orphan*/  xadc_postdisable (struct iio_dev*) ; 
 int xadc_power_adc_b (struct xadc*,int) ; 
 int xadc_update_adc_reg (struct xadc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int xadc_write_adc_reg (struct xadc*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int xadc_preenable(struct iio_dev *indio_dev)
{
	struct xadc *xadc = iio_priv(indio_dev);
	unsigned long scan_mask;
	int seq_mode;
	int ret;

	ret = xadc_update_adc_reg(xadc, XADC_REG_CONF1, XADC_CONF1_SEQ_MASK,
		XADC_CONF1_SEQ_DEFAULT);
	if (ret)
		goto err;

	scan_mask = *indio_dev->active_scan_mask;
	seq_mode = xadc_get_seq_mode(xadc, scan_mask);

	ret = xadc_write_adc_reg(xadc, XADC_REG_SEQ(0), scan_mask & 0xffff);
	if (ret)
		goto err;

	ret = xadc_write_adc_reg(xadc, XADC_REG_SEQ(1), scan_mask >> 16);
	if (ret)
		goto err;

	ret = xadc_power_adc_b(xadc, seq_mode);
	if (ret)
		goto err;

	ret = xadc_update_adc_reg(xadc, XADC_REG_CONF1, XADC_CONF1_SEQ_MASK,
		seq_mode);
	if (ret)
		goto err;

	return 0;
err:
	xadc_postdisable(indio_dev);
	return ret;
}