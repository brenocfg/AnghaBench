#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct twl4030_madc_request {size_t method; int /*<<< orphan*/  raw; int /*<<< orphan*/  rbuf; int /*<<< orphan*/  channels; scalar_t__ do_avg; } ;
struct twl4030_madc_conversion_method {int /*<<< orphan*/  rbase; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  avg; int /*<<< orphan*/  sel; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; TYPE_1__* requests; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int active; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 size_t TWL4030_MADC_RT ; 
 size_t TWL4030_MADC_SW2 ; 
 int /*<<< orphan*/  TWL4030_MODULE_MADC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct twl4030_madc_conversion_method* twl4030_conversion_methods ; 
 TYPE_2__* twl4030_madc ; 
 int twl4030_madc_read_channels (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int twl4030_madc_start_conversion (TYPE_2__*,size_t) ; 
 int twl4030_madc_wait_conversion_ready (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int twl_i2c_write_u16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_madc_conversion(struct twl4030_madc_request *req)
{
	const struct twl4030_madc_conversion_method *method;
	int ret;

	if (!req || !twl4030_madc)
		return -EINVAL;

	mutex_lock(&twl4030_madc->lock);
	if (req->method < TWL4030_MADC_RT || req->method > TWL4030_MADC_SW2) {
		ret = -EINVAL;
		goto out;
	}
	/* Do we have a conversion request ongoing */
	if (twl4030_madc->requests[req->method].active) {
		ret = -EBUSY;
		goto out;
	}
	method = &twl4030_conversion_methods[req->method];
	/* Select channels to be converted */
	ret = twl_i2c_write_u16(TWL4030_MODULE_MADC, req->channels, method->sel);
	if (ret) {
		dev_err(twl4030_madc->dev,
			"unable to write sel register 0x%X\n", method->sel);
		goto out;
	}
	/* Select averaging for all channels if do_avg is set */
	if (req->do_avg) {
		ret = twl_i2c_write_u16(TWL4030_MODULE_MADC, req->channels,
				       method->avg);
		if (ret) {
			dev_err(twl4030_madc->dev,
				"unable to write avg register 0x%X\n",
				method->avg);
			goto out;
		}
	}
	/* With RT method we should not be here anymore */
	if (req->method == TWL4030_MADC_RT) {
		ret = -EINVAL;
		goto out;
	}
	ret = twl4030_madc_start_conversion(twl4030_madc, req->method);
	if (ret < 0)
		goto out;
	twl4030_madc->requests[req->method].active = 1;
	/* Wait until conversion is ready (ctrl register returns EOC) */
	ret = twl4030_madc_wait_conversion_ready(twl4030_madc, 5, method->ctrl);
	if (ret) {
		twl4030_madc->requests[req->method].active = 0;
		goto out;
	}
	ret = twl4030_madc_read_channels(twl4030_madc, method->rbase,
					 req->channels, req->rbuf, req->raw);
	twl4030_madc->requests[req->method].active = 0;

out:
	mutex_unlock(&twl4030_madc->lock);

	return ret;
}