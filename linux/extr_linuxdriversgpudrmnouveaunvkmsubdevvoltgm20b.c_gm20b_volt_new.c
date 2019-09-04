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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_volt {int dummy; } ;
struct nvkm_device_tegra {size_t gpu_speedo_id; } ;
struct nvkm_device {TYPE_1__* func; } ;
struct gk20a_volt {struct nvkm_volt base; } ;
struct TYPE_2__ {struct nvkm_device_tegra* (* tegra ) (struct nvkm_device*) ;} ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int gk20a_volt_ctor (struct nvkm_device*,int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,struct gk20a_volt*) ; 
 int /*<<< orphan*/ * gm20b_cvb_coef ; 
 int /*<<< orphan*/ * gm20b_na_cvb_coef ; 
 struct gk20a_volt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvdev_error (struct nvkm_device*,char*,size_t) ; 
 int /*<<< orphan*/ * speedo_to_vmin ; 
 struct nvkm_device_tegra* stub1 (struct nvkm_device*) ; 

int
gm20b_volt_new(struct nvkm_device *device, int index, struct nvkm_volt **pvolt)
{
	struct nvkm_device_tegra *tdev = device->func->tegra(device);
	struct gk20a_volt *volt;
	u32 vmin;

	if (tdev->gpu_speedo_id >= ARRAY_SIZE(speedo_to_vmin)) {
		nvdev_error(device, "unsupported speedo %d\n",
			    tdev->gpu_speedo_id);
		return -EINVAL;
	}

	volt = kzalloc(sizeof(*volt), GFP_KERNEL);
	if (!volt)
		return -ENOMEM;
	*pvolt = &volt->base;

	vmin = speedo_to_vmin[tdev->gpu_speedo_id];

	if (tdev->gpu_speedo_id >= 1)
		return gk20a_volt_ctor(device, index, gm20b_na_cvb_coef,
				     ARRAY_SIZE(gm20b_na_cvb_coef), vmin, volt);
	else
		return gk20a_volt_ctor(device, index, gm20b_cvb_coef,
					ARRAY_SIZE(gm20b_cvb_coef), vmin, volt);
}