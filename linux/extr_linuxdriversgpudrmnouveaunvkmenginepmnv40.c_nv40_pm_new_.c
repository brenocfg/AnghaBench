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
struct nvkm_specdom {int dummy; } ;
struct nvkm_pm {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct nv40_pm {struct nvkm_pm base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nv40_pm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv40_pm_ ; 
 int nvkm_perfdom_new (struct nvkm_pm*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nvkm_specdom const*) ; 
 int nvkm_pm_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_pm*) ; 

int
nv40_pm_new_(const struct nvkm_specdom *doms, struct nvkm_device *device,
	     int index, struct nvkm_pm **ppm)
{
	struct nv40_pm *pm;
	int ret;

	if (!(pm = kzalloc(sizeof(*pm), GFP_KERNEL)))
		return -ENOMEM;
	*ppm = &pm->base;

	ret = nvkm_pm_ctor(&nv40_pm_, device, index, &pm->base);
	if (ret)
		return ret;

	return nvkm_perfdom_new(&pm->base, "pc", 0, 0, 0, 4, doms);
}