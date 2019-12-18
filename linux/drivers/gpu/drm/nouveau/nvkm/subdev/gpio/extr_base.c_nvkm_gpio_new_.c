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
struct nvkm_gpio_func {int /*<<< orphan*/  lines; } ;
struct nvkm_gpio {int /*<<< orphan*/  event; struct nvkm_gpio_func const* func; int /*<<< orphan*/  subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_gpio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvkm_event_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_gpio ; 
 int /*<<< orphan*/  nvkm_gpio_intr_func ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 

int
nvkm_gpio_new_(const struct nvkm_gpio_func *func, struct nvkm_device *device,
	       int index, struct nvkm_gpio **pgpio)
{
	struct nvkm_gpio *gpio;

	if (!(gpio = *pgpio = kzalloc(sizeof(*gpio), GFP_KERNEL)))
		return -ENOMEM;

	nvkm_subdev_ctor(&nvkm_gpio, device, index, &gpio->subdev);
	gpio->func = func;

	return nvkm_event_init(&nvkm_gpio_intr_func, 2, func->lines,
			       &gpio->event);
}