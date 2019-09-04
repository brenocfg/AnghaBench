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
struct nvkm_gpio {int dummy; } ;
struct nvbios_init {int offset; TYPE_2__* subdev; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct nvkm_gpio* gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_GPIO_UNUSED ; 
 scalar_t__ init_exec (struct nvbios_init*) ; 
 int /*<<< orphan*/  nvkm_gpio_reset (struct nvkm_gpio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void
init_gpio(struct nvbios_init *init)
{
	struct nvkm_gpio *gpio = init->subdev->device->gpio;

	trace("GPIO\n");
	init->offset += 1;

	if (init_exec(init))
		nvkm_gpio_reset(gpio, DCB_GPIO_UNUSED);
}