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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_device {int dummy; } ;
struct gf100_grctx_func {int /*<<< orphan*/  (* r408840 ) (struct gf100_gr*) ;int /*<<< orphan*/  (* r419a3c ) (struct gf100_gr*) ;int /*<<< orphan*/  (* r418e94 ) (struct gf100_gr*) ;int /*<<< orphan*/  (* r419e00 ) (struct gf100_gr*) ;int /*<<< orphan*/  (* r419eb0 ) (struct gf100_gr*) ;int /*<<< orphan*/  (* r418800 ) (struct gf100_gr*) ;int /*<<< orphan*/  (* r419cb8 ) (struct gf100_gr*) ;scalar_t__ mthd; int /*<<< orphan*/  (* r400088 ) (struct gf100_gr*,int) ;scalar_t__ sw_veid_bundle_init; scalar_t__ icmd; int /*<<< orphan*/  (* unkn ) (struct gf100_gr*) ;int /*<<< orphan*/  (* patch_ltc ) (struct gf100_grctx*) ;int /*<<< orphan*/  (* attrib ) (struct gf100_grctx*) ;int /*<<< orphan*/  (* bundle ) (struct gf100_grctx*) ;int /*<<< orphan*/  (* pagepool ) (struct gf100_grctx*) ;int /*<<< orphan*/  ppc; int /*<<< orphan*/  tpc; int /*<<< orphan*/  gpc_1; int /*<<< orphan*/  zcull; int /*<<< orphan*/  gpc_0; int /*<<< orphan*/  hub; } ;
struct gf100_grctx {int dummy; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;
struct gf100_gr {scalar_t__ fuc_method; scalar_t__ fuc_bundle; int /*<<< orphan*/  fuc_sw_ctx; TYPE_4__* func; TYPE_3__ base; } ;
struct TYPE_8__ {struct gf100_grctx_func* grctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  gf100_gr_icmd (struct gf100_gr*,scalar_t__) ; 
 int /*<<< orphan*/  gf100_gr_mmio (struct gf100_gr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf100_gr_mthd (struct gf100_gr*,scalar_t__) ; 
 int /*<<< orphan*/  gf100_gr_wait_idle (struct gf100_gr*) ; 
 int /*<<< orphan*/  gf100_grctx_generate_floorsweep (struct gf100_gr*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_mc_unk260 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct gf100_grctx*) ; 
 int /*<<< orphan*/  stub10 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub11 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub12 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub13 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub14 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub2 (struct gf100_grctx*) ; 
 int /*<<< orphan*/  stub3 (struct gf100_grctx*) ; 
 int /*<<< orphan*/  stub4 (struct gf100_grctx*) ; 
 int /*<<< orphan*/  stub5 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub6 (struct gf100_gr*,int) ; 
 int /*<<< orphan*/  stub7 (struct gf100_gr*,int) ; 
 int /*<<< orphan*/  stub8 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub9 (struct gf100_gr*) ; 

void
gf100_grctx_generate_main(struct gf100_gr *gr, struct gf100_grctx *info)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	const struct gf100_grctx_func *grctx = gr->func->grctx;
	u32 idle_timeout;

	nvkm_mc_unk260(device, 0);

	if (!gr->fuc_sw_ctx) {
		gf100_gr_mmio(gr, grctx->hub);
		gf100_gr_mmio(gr, grctx->gpc_0);
		gf100_gr_mmio(gr, grctx->zcull);
		gf100_gr_mmio(gr, grctx->gpc_1);
		gf100_gr_mmio(gr, grctx->tpc);
		gf100_gr_mmio(gr, grctx->ppc);
	} else {
		gf100_gr_mmio(gr, gr->fuc_sw_ctx);
	}

	gf100_gr_wait_idle(gr);

	idle_timeout = nvkm_mask(device, 0x404154, 0xffffffff, 0x00000000);

	grctx->pagepool(info);
	grctx->bundle(info);
	grctx->attrib(info);
	if (grctx->patch_ltc)
		grctx->patch_ltc(info);
	grctx->unkn(gr);

	gf100_grctx_generate_floorsweep(gr);

	gf100_gr_wait_idle(gr);

	if (grctx->r400088) grctx->r400088(gr, false);
	if (gr->fuc_bundle)
		gf100_gr_icmd(gr, gr->fuc_bundle);
	else
		gf100_gr_icmd(gr, grctx->icmd);
	if (grctx->sw_veid_bundle_init)
		gf100_gr_icmd(gr, grctx->sw_veid_bundle_init);
	if (grctx->r400088) grctx->r400088(gr, true);

	nvkm_wr32(device, 0x404154, idle_timeout);

	if (gr->fuc_method)
		gf100_gr_mthd(gr, gr->fuc_method);
	else
		gf100_gr_mthd(gr, grctx->mthd);
	nvkm_mc_unk260(device, 1);

	if (grctx->r419cb8)
		grctx->r419cb8(gr);
	if (grctx->r418800)
		grctx->r418800(gr);
	if (grctx->r419eb0)
		grctx->r419eb0(gr);
	if (grctx->r419e00)
		grctx->r419e00(gr);
	if (grctx->r418e94)
		grctx->r418e94(gr);
	if (grctx->r419a3c)
		grctx->r419a3c(gr);
	if (grctx->r408840)
		grctx->r408840(gr);
}