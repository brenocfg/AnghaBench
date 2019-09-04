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
struct TYPE_2__ {int /*<<< orphan*/  subdev; } ;
struct nvkm_nvdec {int /*<<< orphan*/  falcon; TYPE_1__ engine; } ;
struct nvkm_engine {int dummy; } ;

/* Variables and functions */
 int nvkm_falcon_v1_new (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 struct nvkm_nvdec* nvkm_nvdec (struct nvkm_engine*) ; 

__attribute__((used)) static int
nvkm_nvdec_oneinit(struct nvkm_engine *engine)
{
	struct nvkm_nvdec *nvdec = nvkm_nvdec(engine);
	return nvkm_falcon_v1_new(&nvdec->engine.subdev, "NVDEC", 0x84000,
				  &nvdec->falcon);
}