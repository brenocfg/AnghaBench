#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u32 ;
struct nvkm_subdev {int dummy; } ;
struct nvkm_gpio {TYPE_1__* func; } ;
struct TYPE_2__ {unsigned long long lines; int /*<<< orphan*/  (* intr_stat ) (struct nvkm_gpio*,unsigned long long*,unsigned long long*) ;int /*<<< orphan*/  (* intr_mask ) (struct nvkm_gpio*,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_GPIO_TOGGLED ; 
 struct nvkm_gpio* nvkm_gpio (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_gpio*,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct nvkm_gpio*,unsigned long long*,unsigned long long*) ; 

__attribute__((used)) static int
nvkm_gpio_fini(struct nvkm_subdev *subdev, bool suspend)
{
	struct nvkm_gpio *gpio = nvkm_gpio(subdev);
	u32 mask = (1ULL << gpio->func->lines) - 1;

	gpio->func->intr_mask(gpio, NVKM_GPIO_TOGGLED, mask, 0);
	gpio->func->intr_stat(gpio, &mask, &mask);
	return 0;
}