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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_timer {struct nvkm_subdev subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PTIMER_DENOMINATOR ; 
 int /*<<< orphan*/  NV04_PTIMER_NUMERATOR ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nv04_timer_init(struct nvkm_timer *tmr)
{
	struct nvkm_subdev *subdev = &tmr->subdev;
	struct nvkm_device *device = subdev->device;
	u32 f = 0; /*XXX: nvclk */
	u32 n, d;

	/* aim for 31.25MHz, which gives us nanosecond timestamps */
	d = 1000000 / 32;
	n = f;

	if (!f) {
		n = nvkm_rd32(device, NV04_PTIMER_NUMERATOR);
		d = nvkm_rd32(device, NV04_PTIMER_DENOMINATOR);
		if (!n || !d) {
			n = 1;
			d = 1;
		}
		nvkm_warn(subdev, "unknown input clock freq\n");
	}

	/* reduce ratio to acceptable values */
	while (((n % 5) == 0) && ((d % 5) == 0)) {
		n /= 5;
		d /= 5;
	}

	while (((n % 2) == 0) && ((d % 2) == 0)) {
		n /= 2;
		d /= 2;
	}

	while (n > 0xffff || d > 0xffff) {
		n >>= 1;
		d >>= 1;
	}

	nvkm_debug(subdev, "input frequency : %dHz\n", f);
	nvkm_debug(subdev, "numerator       : %08x\n", n);
	nvkm_debug(subdev, "denominator     : %08x\n", d);
	nvkm_debug(subdev, "timer frequency : %dHz\n", f * d / n);

	nvkm_wr32(device, NV04_PTIMER_NUMERATOR, n);
	nvkm_wr32(device, NV04_PTIMER_DENOMINATOR, d);
}