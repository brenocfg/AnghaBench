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
struct nvkm_object {int dummy; } ;
struct nvkm_nvsw {TYPE_1__* func; } ;
struct TYPE_2__ {int (* mthd ) (struct nvkm_nvsw*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENODEV ; 
 struct nvkm_nvsw* nvkm_nvsw (struct nvkm_object*) ; 
 int stub1 (struct nvkm_nvsw*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_nvsw_mthd_(struct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	struct nvkm_nvsw *nvsw = nvkm_nvsw(object);
	if (nvsw->func->mthd)
		return nvsw->func->mthd(nvsw, mthd, data, size);
	return -ENODEV;
}