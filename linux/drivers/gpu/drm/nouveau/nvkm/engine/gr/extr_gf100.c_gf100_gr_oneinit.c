#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_gr {int dummy; } ;
struct nvkm_device {int /*<<< orphan*/  pmu; } ;
struct TYPE_9__ {int /*<<< orphan*/  falcon; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  falcon; } ;
struct TYPE_6__ {struct nvkm_subdev subdev; } ;
struct TYPE_7__ {TYPE_1__ engine; } ;
struct gf100_gr {int gpc_nr; int* tpc_nr; int tpc_total; int* ppc_nr; int** ppc_tpc_mask; int* ppc_mask; scalar_t__** ppc_tpc_nr; scalar_t__ ppc_tpc_min; scalar_t__ ppc_tpc_max; TYPE_5__* func; int /*<<< orphan*/  tile; int /*<<< orphan*/  tpc_max; int /*<<< orphan*/  rop_nr; TYPE_4__ gpccs; TYPE_3__ fecs; TYPE_2__ base; } ;
struct TYPE_10__ {int ppc_nr; int /*<<< orphan*/  (* oneinit_sm_id ) (struct gf100_gr*) ;int /*<<< orphan*/  (* oneinit_tiles ) (struct gf100_gr*) ;int /*<<< orphan*/  (* rops ) (struct gf100_gr*) ;} ;

/* Variables and functions */
 int GPC_UNIT (int,int) ; 
 struct gf100_gr* gf100_gr (struct nvkm_gr*) ; 
 scalar_t__ hweight8 (int) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nvkm_falcon_v1_new (struct nvkm_subdev*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_pmu_pgob (int /*<<< orphan*/ ,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  stub1 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub2 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub3 (struct gf100_gr*) ; 

__attribute__((used)) static int
gf100_gr_oneinit(struct nvkm_gr *base)
{
	struct gf100_gr *gr = gf100_gr(base);
	struct nvkm_subdev *subdev = &gr->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	int i, j;
	int ret;

	ret = nvkm_falcon_v1_new(subdev, "FECS", 0x409000, &gr->fecs.falcon);
	if (ret)
		return ret;

	mutex_init(&gr->fecs.mutex);

	ret = nvkm_falcon_v1_new(subdev, "GPCCS", 0x41a000, &gr->gpccs.falcon);
	if (ret)
		return ret;

	nvkm_pmu_pgob(device->pmu, false);

	gr->rop_nr = gr->func->rops(gr);
	gr->gpc_nr = nvkm_rd32(device, 0x409604) & 0x0000001f;
	for (i = 0; i < gr->gpc_nr; i++) {
		gr->tpc_nr[i]  = nvkm_rd32(device, GPC_UNIT(i, 0x2608));
		gr->tpc_max = max(gr->tpc_max, gr->tpc_nr[i]);
		gr->tpc_total += gr->tpc_nr[i];
		gr->ppc_nr[i]  = gr->func->ppc_nr;
		for (j = 0; j < gr->ppc_nr[i]; j++) {
			gr->ppc_tpc_mask[i][j] =
				nvkm_rd32(device, GPC_UNIT(i, 0x0c30 + (j * 4)));
			if (gr->ppc_tpc_mask[i][j] == 0)
				continue;
			gr->ppc_mask[i] |= (1 << j);
			gr->ppc_tpc_nr[i][j] = hweight8(gr->ppc_tpc_mask[i][j]);
			if (gr->ppc_tpc_min == 0 ||
			    gr->ppc_tpc_min > gr->ppc_tpc_nr[i][j])
				gr->ppc_tpc_min = gr->ppc_tpc_nr[i][j];
			if (gr->ppc_tpc_max < gr->ppc_tpc_nr[i][j])
				gr->ppc_tpc_max = gr->ppc_tpc_nr[i][j];
		}
	}

	memset(gr->tile, 0xff, sizeof(gr->tile));
	gr->func->oneinit_tiles(gr);
	gr->func->oneinit_sm_id(gr);
	return 0;
}