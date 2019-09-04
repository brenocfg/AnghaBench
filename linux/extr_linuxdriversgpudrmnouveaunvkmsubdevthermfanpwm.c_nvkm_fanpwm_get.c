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
typedef  int u32 ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct nvkm_therm {TYPE_2__* func; TYPE_1__ subdev; scalar_t__ fan; } ;
struct nvkm_gpio {int dummy; } ;
struct TYPE_6__ {int* log; int /*<<< orphan*/  line; int /*<<< orphan*/  func; } ;
struct nvkm_fanpwm {TYPE_3__ func; } ;
struct nvkm_device {int card_type; struct nvkm_gpio* gpio; } ;
struct TYPE_5__ {int (* pwm_get ) (struct nvkm_therm*,int /*<<< orphan*/ ,int*,int*) ;} ;

/* Variables and functions */
 int NV_40 ; 
 int max (int,int) ; 
 int nvkm_gpio_get (struct nvkm_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct nvkm_therm*,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int
nvkm_fanpwm_get(struct nvkm_therm *therm)
{
	struct nvkm_fanpwm *fan = (void *)therm->fan;
	struct nvkm_device *device = therm->subdev.device;
	struct nvkm_gpio *gpio = device->gpio;
	int card_type = device->card_type;
	u32 divs, duty;
	int ret;

	ret = therm->func->pwm_get(therm, fan->func.line, &divs, &duty);
	if (ret == 0 && divs) {
		divs = max(divs, duty);
		if (card_type <= NV_40 || (fan->func.log[0] & 1))
			duty = divs - duty;
		return (duty * 100) / divs;
	}

	return nvkm_gpio_get(gpio, 0, fan->func.func, fan->func.line) * 100;
}