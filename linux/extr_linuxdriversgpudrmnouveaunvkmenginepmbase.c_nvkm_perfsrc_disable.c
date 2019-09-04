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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct TYPE_2__ {struct nvkm_subdev subdev; } ;
struct nvkm_pm {TYPE_1__ engine; } ;
struct nvkm_perfsrc {int mask; int shift; int /*<<< orphan*/  addr; scalar_t__ enable; } ;
struct nvkm_perfsig {int dummy; } ;
struct nvkm_perfdom {int dummy; } ;
struct nvkm_perfctr {scalar_t__** source; int /*<<< orphan*/ * signal; int /*<<< orphan*/  domain; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct nvkm_perfsig* nvkm_perfsig_find (struct nvkm_pm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvkm_perfdom**) ; 
 struct nvkm_perfsrc* nvkm_perfsrc_find (struct nvkm_pm*,struct nvkm_perfsig*,scalar_t__) ; 

__attribute__((used)) static int
nvkm_perfsrc_disable(struct nvkm_pm *pm, struct nvkm_perfctr *ctr)
{
	struct nvkm_subdev *subdev = &pm->engine.subdev;
	struct nvkm_device *device = subdev->device;
	struct nvkm_perfdom *dom = NULL;
	struct nvkm_perfsig *sig;
	struct nvkm_perfsrc *src;
	u32 mask;
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 8 && ctr->source[i][j]; j++) {
			sig = nvkm_perfsig_find(pm, ctr->domain,
						ctr->signal[i], &dom);
			if (!sig)
				return -EINVAL;

			src = nvkm_perfsrc_find(pm, sig, ctr->source[i][j]);
			if (!src)
				return -EINVAL;

			/* unset enable bit if needed */
			mask = 0x00000000;
			if (src->enable)
				mask = 0x80000000;
			mask |= (src->mask << src->shift);

			/* disable the source */
			nvkm_mask(device, src->addr, mask, 0);
			nvkm_debug(subdev, "disabled source %08x %08x\n",
				   src->addr, mask);
		}
	}
	return 0;
}