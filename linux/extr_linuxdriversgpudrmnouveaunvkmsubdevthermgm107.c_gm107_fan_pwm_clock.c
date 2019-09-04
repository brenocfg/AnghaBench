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
struct TYPE_4__ {TYPE_1__* device; } ;
struct nvkm_therm {TYPE_2__ subdev; } ;
struct TYPE_3__ {int crystal; } ;

/* Variables and functions */

__attribute__((used)) static int
gm107_fan_pwm_clock(struct nvkm_therm *therm, int line)
{
	return therm->subdev.device->crystal * 1000;
}