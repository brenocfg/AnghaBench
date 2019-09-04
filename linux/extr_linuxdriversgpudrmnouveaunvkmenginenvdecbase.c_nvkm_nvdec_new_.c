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
struct nvkm_nvdec {int /*<<< orphan*/  engine; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_nvdec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvkm_engine_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_nvdec ; 

int
nvkm_nvdec_new_(struct nvkm_device *device, int index,
		struct nvkm_nvdec **pnvdec)
{
	struct nvkm_nvdec *nvdec;

	if (!(nvdec = *pnvdec = kzalloc(sizeof(*nvdec), GFP_KERNEL)))
		return -ENOMEM;

	return nvkm_engine_ctor(&nvkm_nvdec, device, index, true,
				&nvdec->engine);
}