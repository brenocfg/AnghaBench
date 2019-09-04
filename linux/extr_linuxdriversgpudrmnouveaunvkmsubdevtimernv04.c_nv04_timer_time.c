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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_timer {struct nvkm_subdev subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PTIMER_TIME_0 ; 
 int /*<<< orphan*/  NV04_PTIMER_TIME_1 ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

void
nv04_timer_time(struct nvkm_timer *tmr, u64 time)
{
	struct nvkm_subdev *subdev = &tmr->subdev;
	struct nvkm_device *device = subdev->device;
	u32 hi = upper_32_bits(time);
	u32 lo = lower_32_bits(time);

	nvkm_debug(subdev, "time low        : %08x\n", lo);
	nvkm_debug(subdev, "time high       : %08x\n", hi);

	nvkm_wr32(device, NV04_PTIMER_TIME_1, hi);
	nvkm_wr32(device, NV04_PTIMER_TIME_0, lo);
}