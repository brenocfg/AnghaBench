#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvkm_device_tegra {int /*<<< orphan*/  gpu_speedo; int /*<<< orphan*/  vdd; } ;
struct nvkm_device {TYPE_1__* func; } ;
struct TYPE_6__ {int vid_nr; TYPE_2__* vid; int /*<<< orphan*/  subdev; } ;
struct gk20a_volt {TYPE_3__ base; int /*<<< orphan*/  vdd; } ;
struct cvb_coef {int dummy; } ;
struct TYPE_5__ {int vid; int /*<<< orphan*/  uv; } ;
struct TYPE_4__ {struct nvkm_device_tegra* (* tegra ) (struct nvkm_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  gk20a_volt ; 
 int /*<<< orphan*/  gk20a_volt_calc_voltage (struct cvb_coef const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_debug (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  nvkm_volt_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,TYPE_3__*) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 
 struct nvkm_device_tegra* stub1 (struct nvkm_device*) ; 

int
gk20a_volt_ctor(struct nvkm_device *device, int index,
		const struct cvb_coef *coefs, int nb_coefs,
		int vmin, struct gk20a_volt *volt)
{
	struct nvkm_device_tegra *tdev = device->func->tegra(device);
	int i, uv;

	nvkm_volt_ctor(&gk20a_volt, device, index, &volt->base);

	uv = regulator_get_voltage(tdev->vdd);
	nvkm_debug(&volt->base.subdev, "the default voltage is %duV\n", uv);

	volt->vdd = tdev->vdd;

	volt->base.vid_nr = nb_coefs;
	for (i = 0; i < volt->base.vid_nr; i++) {
		volt->base.vid[i].vid = i;
		volt->base.vid[i].uv = max(
			gk20a_volt_calc_voltage(&coefs[i], tdev->gpu_speedo),
			vmin);
		nvkm_debug(&volt->base.subdev, "%2d: vid=%d, uv=%d\n", i,
			   volt->base.vid[i].vid, volt->base.vid[i].uv);
	}

	return 0;
}