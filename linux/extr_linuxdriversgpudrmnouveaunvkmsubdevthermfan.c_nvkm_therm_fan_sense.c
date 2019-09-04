#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_timer {int dummy; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct nvkm_therm {TYPE_4__* fan; TYPE_2__* func; TYPE_1__ subdev; } ;
struct nvkm_gpio {int dummy; } ;
struct nvkm_device {struct nvkm_gpio* gpio; struct nvkm_timer* timer; } ;
struct TYPE_7__ {int /*<<< orphan*/  line; int /*<<< orphan*/  func; } ;
struct TYPE_8__ {TYPE_3__ tach; } ;
struct TYPE_6__ {int (* fan_sense ) (struct nvkm_therm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_GPIO_UNUSED ; 
 int ENODEV ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int nvkm_gpio_get (struct nvkm_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvkm_timer_read (struct nvkm_timer*) ; 
 int stub1 (struct nvkm_therm*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int
nvkm_therm_fan_sense(struct nvkm_therm *therm)
{
	struct nvkm_device *device = therm->subdev.device;
	struct nvkm_timer *tmr = device->timer;
	struct nvkm_gpio *gpio = device->gpio;
	u32 cycles, cur, prev;
	u64 start, end, tach;

	if (therm->func->fan_sense)
		return therm->func->fan_sense(therm);

	if (therm->fan->tach.func == DCB_GPIO_UNUSED)
		return -ENODEV;

	/* Time a complete rotation and extrapolate to RPM:
	 * When the fan spins, it changes the value of GPIO FAN_SENSE.
	 * We get 4 changes (0 -> 1 -> 0 -> 1) per complete rotation.
	 */
	start = nvkm_timer_read(tmr);
	prev = nvkm_gpio_get(gpio, 0, therm->fan->tach.func,
				      therm->fan->tach.line);
	cycles = 0;
	do {
		usleep_range(500, 1000); /* supports 0 < rpm < 7500 */

		cur = nvkm_gpio_get(gpio, 0, therm->fan->tach.func,
					     therm->fan->tach.line);
		if (prev != cur) {
			if (!start)
				start = nvkm_timer_read(tmr);
			cycles++;
			prev = cur;
		}
	} while (cycles < 5 && nvkm_timer_read(tmr) - start < 250000000);
	end = nvkm_timer_read(tmr);

	if (cycles == 5) {
		tach = (u64)60000000000ULL;
		do_div(tach, (end - start));
		return tach;
	} else
		return 0;
}