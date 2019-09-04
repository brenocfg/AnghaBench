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
struct nvkm_ltc_func {int /*<<< orphan*/  zbc; } ;
struct nvkm_ltc {int zbc_min; scalar_t__ zbc_max; struct nvkm_ltc_func const* func; int /*<<< orphan*/  subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVKM_LTC_MAX_ZBC_CNT ; 
 struct nvkm_ltc* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_ltc ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 

int
nvkm_ltc_new_(const struct nvkm_ltc_func *func, struct nvkm_device *device,
	      int index, struct nvkm_ltc **pltc)
{
	struct nvkm_ltc *ltc;

	if (!(ltc = *pltc = kzalloc(sizeof(*ltc), GFP_KERNEL)))
		return -ENOMEM;

	nvkm_subdev_ctor(&nvkm_ltc, device, index, &ltc->subdev);
	ltc->func = func;
	ltc->zbc_min = 1; /* reserve 0 for disabled */
	ltc->zbc_max = min(func->zbc, NVKM_LTC_MAX_ZBC_CNT) - 1;
	return 0;
}