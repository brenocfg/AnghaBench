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
typedef  int /*<<< orphan*/  u8 ;
struct nvkm_gpio {TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct nvkm_gpio*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nvkm_gpio*,int /*<<< orphan*/ ) ; 

void
nvkm_gpio_reset(struct nvkm_gpio *gpio, u8 func)
{
	if (gpio->func->reset)
		gpio->func->reset(gpio, func);
}