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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_timer {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PTIMER_TIME_0 ; 
 int /*<<< orphan*/  NV04_PTIMER_TIME_1 ; 
 scalar_t__ nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 

u64
nv04_timer_read(struct nvkm_timer *tmr)
{
	struct nvkm_device *device = tmr->subdev.device;
	u32 hi, lo;

	do {
		hi = nvkm_rd32(device, NV04_PTIMER_TIME_1);
		lo = nvkm_rd32(device, NV04_PTIMER_TIME_0);
	} while (hi != nvkm_rd32(device, NV04_PTIMER_TIME_1));

	return ((u64)hi << 32 | lo);
}