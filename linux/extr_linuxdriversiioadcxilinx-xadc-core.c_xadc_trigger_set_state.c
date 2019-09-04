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
struct xadc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; struct iio_trigger* trigger; struct iio_trigger* convst_trigger; } ;
struct iio_trigger {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned int XADC_AXI_INT_EOS ; 
 int /*<<< orphan*/  XADC_AXI_REG_IPIER ; 
 int /*<<< orphan*/  XADC_AXI_REG_IPISR ; 
 unsigned int XADC_CONF0_EC ; 
 int /*<<< orphan*/  XADC_REG_CONF1 ; 
 int _xadc_update_adc_reg (struct xadc*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct xadc* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xadc_read_reg (struct xadc*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  xadc_write_reg (struct xadc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int xadc_trigger_set_state(struct iio_trigger *trigger, bool state)
{
	struct xadc *xadc = iio_trigger_get_drvdata(trigger);
	unsigned long flags;
	unsigned int convst;
	unsigned int val;
	int ret = 0;

	mutex_lock(&xadc->mutex);

	if (state) {
		/* Only one of the two triggers can be active at the a time. */
		if (xadc->trigger != NULL) {
			ret = -EBUSY;
			goto err_out;
		} else {
			xadc->trigger = trigger;
			if (trigger == xadc->convst_trigger)
				convst = XADC_CONF0_EC;
			else
				convst = 0;
		}
		ret = _xadc_update_adc_reg(xadc, XADC_REG_CONF1, XADC_CONF0_EC,
					convst);
		if (ret)
			goto err_out;
	} else {
		xadc->trigger = NULL;
	}

	spin_lock_irqsave(&xadc->lock, flags);
	xadc_read_reg(xadc, XADC_AXI_REG_IPIER, &val);
	xadc_write_reg(xadc, XADC_AXI_REG_IPISR, val & XADC_AXI_INT_EOS);
	if (state)
		val |= XADC_AXI_INT_EOS;
	else
		val &= ~XADC_AXI_INT_EOS;
	xadc_write_reg(xadc, XADC_AXI_REG_IPIER, val);
	spin_unlock_irqrestore(&xadc->lock, flags);

err_out:
	mutex_unlock(&xadc->mutex);

	return ret;
}