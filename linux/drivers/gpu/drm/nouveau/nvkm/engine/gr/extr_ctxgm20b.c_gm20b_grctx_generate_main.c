#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_device {int dummy; } ;
struct gf100_grctx_func {int /*<<< orphan*/  (* bundle ) (struct gf100_grctx*) ;int /*<<< orphan*/  (* pagepool ) (struct gf100_grctx*) ;int /*<<< orphan*/  (* unkn ) (struct gf100_gr*) ;int /*<<< orphan*/  (* attrib ) (struct gf100_grctx*) ;} ;
struct gf100_grctx {int dummy; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;
struct gf100_gr {int tpc_total; int gpc_nr; int* tpc_nr; int /*<<< orphan*/  fuc_bundle; int /*<<< orphan*/  fuc_method; int /*<<< orphan*/  fuc_sw_ctx; TYPE_4__* func; TYPE_3__ base; } ;
struct TYPE_8__ {struct gf100_grctx_func* grctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  gf100_gr_icmd (struct gf100_gr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf100_gr_mmio (struct gf100_gr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf100_gr_mthd (struct gf100_gr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf100_gr_wait_idle (struct gf100_gr*) ; 
 int /*<<< orphan*/  gf100_grctx_generate_floorsweep (struct gf100_gr*) ; 
 int /*<<< orphan*/  gm200_grctx_generate_smid_config (struct gf100_gr*) ; 
 int nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct gf100_grctx*) ; 
 int /*<<< orphan*/  stub2 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub3 (struct gf100_grctx*) ; 
 int /*<<< orphan*/  stub4 (struct gf100_grctx*) ; 

__attribute__((used)) static void
gm20b_grctx_generate_main(struct gf100_gr *gr, struct gf100_grctx *info)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	const struct gf100_grctx_func *grctx = gr->func->grctx;
	u32 idle_timeout;
	int i, tmp;

	gf100_gr_mmio(gr, gr->fuc_sw_ctx);

	gf100_gr_wait_idle(gr);

	idle_timeout = nvkm_mask(device, 0x404154, 0xffffffff, 0x00000000);

	grctx->attrib(info);

	grctx->unkn(gr);

	gf100_grctx_generate_floorsweep(gr);

	for (i = 0; i < 8; i++)
		nvkm_wr32(device, 0x4064d0 + (i * 0x04), 0x00000000);

	nvkm_wr32(device, 0x405b00, (gr->tpc_total << 8) | gr->gpc_nr);

	nvkm_wr32(device, 0x408908, nvkm_rd32(device, 0x410108) | 0x80000000);

	for (tmp = 0, i = 0; i < gr->gpc_nr; i++)
		tmp |= ((1 << gr->tpc_nr[i]) - 1) << (i * 4);
	nvkm_wr32(device, 0x4041c4, tmp);

	gm200_grctx_generate_smid_config(gr);

	gf100_gr_wait_idle(gr);

	nvkm_wr32(device, 0x404154, idle_timeout);
	gf100_gr_wait_idle(gr);

	gf100_gr_mthd(gr, gr->fuc_method);
	gf100_gr_wait_idle(gr);

	gf100_gr_icmd(gr, gr->fuc_bundle);
	grctx->pagepool(info);
	grctx->bundle(info);
}