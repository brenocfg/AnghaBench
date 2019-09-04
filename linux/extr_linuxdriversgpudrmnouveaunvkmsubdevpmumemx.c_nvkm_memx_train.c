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
struct nvkm_memx {TYPE_1__* pmu; } ;
struct TYPE_2__ {int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMX_TRAIN ; 
 int /*<<< orphan*/  memx_cmd (struct nvkm_memx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_debug (int /*<<< orphan*/ *,char*) ; 

void
nvkm_memx_train(struct nvkm_memx *memx)
{
	nvkm_debug(&memx->pmu->subdev, "   MEM TRAIN\n");
	memx_cmd(memx, MEMX_TRAIN, 0, NULL);
}