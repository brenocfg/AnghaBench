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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct cx18_gpio_i2c_slave_reset {int active_lo_mask; int msecs_asserted; int msecs_recovery; int ir_reset_mask; int /*<<< orphan*/  active_hi_mask; } ;
struct cx18 {TYPE_2__* card; } ;
struct TYPE_4__ {int xceive_pin; TYPE_1__* tuners; struct cx18_gpio_i2c_slave_reset gpio_i2c_slave_reset; } ;
struct TYPE_3__ {int /*<<< orphan*/  tuner; } ;

/* Variables and functions */
#define  CX18_GPIO_RESET_I2C 130 
#define  CX18_GPIO_RESET_XC2028 129 
#define  CX18_GPIO_RESET_Z8F0811 128 
 int /*<<< orphan*/  TUNER_XC2028 ; 
 int /*<<< orphan*/  gpio_reset_seq (struct cx18*,int,int /*<<< orphan*/ ,int,int) ; 
 struct cx18* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int resetctrl_reset(struct v4l2_subdev *sd, u32 val)
{
	struct cx18 *cx = v4l2_get_subdevdata(sd);
	const struct cx18_gpio_i2c_slave_reset *p;

	p = &cx->card->gpio_i2c_slave_reset;
	switch (val) {
	case CX18_GPIO_RESET_I2C:
		gpio_reset_seq(cx, p->active_lo_mask, p->active_hi_mask,
			       p->msecs_asserted, p->msecs_recovery);
		break;
	case CX18_GPIO_RESET_Z8F0811:
		/*
		 * Assert timing for the Z8F0811 on HVR-1600 boards:
		 * 1. Assert RESET for min of 4 clock cycles at 18.432 MHz to
		 *    initiate
		 * 2. Reset then takes 66 WDT cycles at 10 kHz + 16 xtal clock
		 *    cycles (6,601,085 nanoseconds ~= 7 milliseconds)
		 * 3. DBG pin must be high before chip exits reset for normal
		 *    operation.  DBG is open drain and hopefully pulled high
		 *    since we don't normally drive it (GPIO 1?) for the
		 *    HVR-1600
		 * 4. Z8F0811 won't exit reset until RESET is deasserted
		 * 5. Zilog comes out of reset, loads reset vector address and
		 *    executes from there. Required recovery delay unknown.
		 */
		gpio_reset_seq(cx, p->ir_reset_mask, 0,
			       p->msecs_asserted, p->msecs_recovery);
		break;
	case CX18_GPIO_RESET_XC2028:
		if (cx->card->tuners[0].tuner == TUNER_XC2028)
			gpio_reset_seq(cx, (1 << cx->card->xceive_pin), 0,
				       1, 1);
		break;
	}
	return 0;
}