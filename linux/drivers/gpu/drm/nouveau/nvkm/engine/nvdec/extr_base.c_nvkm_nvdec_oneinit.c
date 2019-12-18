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
struct nvkm_subdev {int /*<<< orphan*/  index; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {struct nvkm_subdev subdev; } ;
struct nvkm_nvdec {int /*<<< orphan*/  falcon; int /*<<< orphan*/  addr; TYPE_1__ engine; } ;
struct nvkm_engine {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int nvkm_falcon_v1_new (struct nvkm_subdev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nvkm_nvdec* nvkm_nvdec (struct nvkm_engine*) ; 
 int /*<<< orphan*/  nvkm_top_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_nvdec_oneinit(struct nvkm_engine *engine)
{
	struct nvkm_nvdec *nvdec = nvkm_nvdec(engine);
	struct nvkm_subdev *subdev = &nvdec->engine.subdev;

	nvdec->addr = nvkm_top_addr(subdev->device, subdev->index);
	if (!nvdec->addr)
		return -EINVAL;

	/*XXX: fix naming of this when adding support for multiple-NVDEC */
	return nvkm_falcon_v1_new(subdev, "NVDEC", nvdec->addr,
				  &nvdec->falcon);
}