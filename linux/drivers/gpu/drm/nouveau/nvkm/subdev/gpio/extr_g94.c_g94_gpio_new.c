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
struct nvkm_gpio {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g94_gpio ; 
 int nvkm_gpio_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_gpio**) ; 

int
g94_gpio_new(struct nvkm_device *device, int index, struct nvkm_gpio **pgpio)
{
	return nvkm_gpio_new_(&g94_gpio, device, index, pgpio);
}