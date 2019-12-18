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
struct i2c_algo_bit_data {struct cx18_i2c_algo_callback_data* data; } ;
struct cx18_i2c_algo_callback_data {struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  sd_resetctrl; TYPE_2__* card; } ;
struct TYPE_4__ {TYPE_1__* tuners; } ;
struct TYPE_3__ {scalar_t__ tuner; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  CX18_GPIO_RESET_XC2028 ; 
 scalar_t__ TUNER_XC2028 ; 
 int XC2028_TUNER_RESET ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  reset ; 
 int v4l2_subdev_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cx18_reset_tuner_gpio(void *dev, int component, int cmd, int value)
{
	struct i2c_algo_bit_data *algo = dev;
	struct cx18_i2c_algo_callback_data *cb_data = algo->data;
	struct cx18 *cx = cb_data->cx;

	if (cmd != XC2028_TUNER_RESET ||
	    cx->card->tuners[0].tuner != TUNER_XC2028)
		return 0;

	CX18_DEBUG_INFO("Resetting XCeive tuner\n");
	return v4l2_subdev_call(&cx->sd_resetctrl,
				core, reset, CX18_GPIO_RESET_XC2028);
}