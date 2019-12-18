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
struct nvkm_volt {int dummy; } ;
struct nvkm_subdev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,...) ; 
 struct nvkm_volt* nvkm_volt (struct nvkm_subdev*) ; 
 int nvkm_volt_get (struct nvkm_volt*) ; 

__attribute__((used)) static int
nvkm_volt_init(struct nvkm_subdev *subdev)
{
	struct nvkm_volt *volt = nvkm_volt(subdev);
	int ret = nvkm_volt_get(volt);
	if (ret < 0) {
		if (ret != -ENODEV)
			nvkm_debug(subdev, "current voltage unknown\n");
		return 0;
	}
	nvkm_debug(subdev, "current voltage: %duv\n", ret);
	return 0;
}