#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cx18 {int gpio_dir; int gpio_val; int /*<<< orphan*/  gpio_lock; TYPE_3__* card; } ;
struct TYPE_4__ {int direction; int initial_value; } ;
struct TYPE_6__ {int xceive_pin; TYPE_2__* tuners; TYPE_1__ gpio_init; } ;
struct TYPE_5__ {scalar_t__ tuner; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CX18_REG_GPIO_DIR1 ; 
 int /*<<< orphan*/  CX18_REG_GPIO_DIR2 ; 
 int /*<<< orphan*/  CX18_REG_GPIO_OUT1 ; 
 int /*<<< orphan*/  CX18_REG_GPIO_OUT2 ; 
 scalar_t__ TUNER_XC2028 ; 
 int /*<<< orphan*/  cx18_read_reg (struct cx18*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_write (struct cx18*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void cx18_gpio_init(struct cx18 *cx)
{
	mutex_lock(&cx->gpio_lock);
	cx->gpio_dir = cx->card->gpio_init.direction;
	cx->gpio_val = cx->card->gpio_init.initial_value;

	if (cx->card->tuners[0].tuner == TUNER_XC2028) {
		cx->gpio_dir |= 1 << cx->card->xceive_pin;
		cx->gpio_val |= 1 << cx->card->xceive_pin;
	}

	if (cx->gpio_dir == 0) {
		mutex_unlock(&cx->gpio_lock);
		return;
	}

	CX18_DEBUG_INFO("GPIO initial dir: %08x/%08x out: %08x/%08x\n",
			cx18_read_reg(cx, CX18_REG_GPIO_DIR1),
			cx18_read_reg(cx, CX18_REG_GPIO_DIR2),
			cx18_read_reg(cx, CX18_REG_GPIO_OUT1),
			cx18_read_reg(cx, CX18_REG_GPIO_OUT2));

	gpio_write(cx);
	mutex_unlock(&cx->gpio_lock);
}