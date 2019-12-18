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
struct nvkm_gpio {TYPE_1__* func; } ;
struct TYPE_2__ {int (* drive ) (struct nvkm_gpio*,int,int,int) ;} ;

/* Variables and functions */
 int stub1 (struct nvkm_gpio*,int,int,int) ; 

__attribute__((used)) static int
nvkm_gpio_drive(struct nvkm_gpio *gpio, int idx, int line, int dir, int out)
{
	return gpio->func->drive(gpio, line, dir, out);
}