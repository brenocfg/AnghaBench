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
typedef  int u8 ;
struct twl4030_madc_request {int result_pending; size_t method; scalar_t__ active; int /*<<< orphan*/  raw; int /*<<< orphan*/  rbuf; int /*<<< orphan*/  channels; } ;
struct twl4030_madc_data {int /*<<< orphan*/  lock; struct twl4030_madc_request* requests; int /*<<< orphan*/  dev; int /*<<< orphan*/  imr; int /*<<< orphan*/  isr; } ;
struct twl4030_madc_conversion_method {int /*<<< orphan*/  rbase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int TWL4030_MADC_NUM_METHODS ; 
 int /*<<< orphan*/  TWL4030_MODULE_MADC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct twl4030_madc_conversion_method* twl4030_conversion_methods ; 
 int twl4030_madc_disable_irq (struct twl4030_madc_data*,int) ; 
 int twl4030_madc_read_channels (struct twl4030_madc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t twl4030_madc_threaded_irq_handler(int irq, void *_madc)
{
	struct twl4030_madc_data *madc = _madc;
	const struct twl4030_madc_conversion_method *method;
	u8 isr_val, imr_val;
	int i, len, ret;
	struct twl4030_madc_request *r;

	mutex_lock(&madc->lock);
	ret = twl_i2c_read_u8(TWL4030_MODULE_MADC, &isr_val, madc->isr);
	if (ret) {
		dev_err(madc->dev, "unable to read isr register 0x%X\n",
			madc->isr);
		goto err_i2c;
	}
	ret = twl_i2c_read_u8(TWL4030_MODULE_MADC, &imr_val, madc->imr);
	if (ret) {
		dev_err(madc->dev, "unable to read imr register 0x%X\n",
			madc->imr);
		goto err_i2c;
	}
	isr_val &= ~imr_val;
	for (i = 0; i < TWL4030_MADC_NUM_METHODS; i++) {
		if (!(isr_val & (1 << i)))
			continue;
		ret = twl4030_madc_disable_irq(madc, i);
		if (ret < 0)
			dev_dbg(madc->dev, "Disable interrupt failed %d\n", i);
		madc->requests[i].result_pending = 1;
	}
	for (i = 0; i < TWL4030_MADC_NUM_METHODS; i++) {
		r = &madc->requests[i];
		/* No pending results for this method, move to next one */
		if (!r->result_pending)
			continue;
		method = &twl4030_conversion_methods[r->method];
		/* Read results */
		len = twl4030_madc_read_channels(madc, method->rbase,
						 r->channels, r->rbuf, r->raw);
		/* Free request */
		r->result_pending = 0;
		r->active = 0;
	}
	mutex_unlock(&madc->lock);

	return IRQ_HANDLED;

err_i2c:
	/*
	 * In case of error check whichever request is active
	 * and service the same.
	 */
	for (i = 0; i < TWL4030_MADC_NUM_METHODS; i++) {
		r = &madc->requests[i];
		if (r->active == 0)
			continue;
		method = &twl4030_conversion_methods[r->method];
		/* Read results */
		len = twl4030_madc_read_channels(madc, method->rbase,
						 r->channels, r->rbuf, r->raw);
		/* Free request */
		r->result_pending = 0;
		r->active = 0;
	}
	mutex_unlock(&madc->lock);

	return IRQ_HANDLED;
}