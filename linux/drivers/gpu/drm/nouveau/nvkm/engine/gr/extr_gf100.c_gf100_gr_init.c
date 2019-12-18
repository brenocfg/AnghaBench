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
struct nvkm_device {int /*<<< orphan*/  therm; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;
struct TYPE_7__ {TYPE_2__ engine; } ;
struct gf100_gr {int gpc_nr; int* tpc_nr; int rop_nr; TYPE_4__* func; scalar_t__ fuc_sw_nonctx; TYPE_3__ base; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* init_4188a4 ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_400054 ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_shader_exceptions ) (struct gf100_gr*,int,int) ;int /*<<< orphan*/  (* init_504430 ) (struct gf100_gr*,int,int) ;int /*<<< orphan*/  (* init_tex_hww_esr ) (struct gf100_gr*,int,int) ;int /*<<< orphan*/  (* init_ppc_exceptions ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_419c9c ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_419eb4 ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_419cc0 ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_sked_hww_esr ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_40601c ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_ds_hww_esr_2 ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_fecs_exceptions ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_swdx_pes_mask ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_bios_2 ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_rop_active_fbps ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_num_active_ltcs ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_zcull ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_vsc_stream_master ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_bios ) (struct gf100_gr*) ;scalar_t__ clkgate_pack; int /*<<< orphan*/  (* init_r405a14 ) (struct gf100_gr*) ;scalar_t__ mmio; int /*<<< orphan*/  (* init_gpc_mmu ) (struct gf100_gr*) ;int /*<<< orphan*/  (* init_419bd8 ) (struct gf100_gr*) ;} ;

/* Variables and functions */
 int GPC_UNIT (int,int) ; 
 int ROP_UNIT (int,int) ; 
 int TPC_UNIT (int,int,int) ; 
 int gf100_gr_init_ctxctl (struct gf100_gr*) ; 
 int /*<<< orphan*/  gf100_gr_mmio (struct gf100_gr*,scalar_t__) ; 
 int /*<<< orphan*/  gf100_gr_wait_idle (struct gf100_gr*) ; 
 int /*<<< orphan*/  gf100_gr_zbc_init (struct gf100_gr*) ; 
 int /*<<< orphan*/  nvkm_therm_clkgate_init (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub10 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub11 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub12 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub13 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub14 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub15 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub16 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub17 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub18 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub19 (struct gf100_gr*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub20 (struct gf100_gr*,int,int) ; 
 int /*<<< orphan*/  stub21 (struct gf100_gr*,int,int) ; 
 int /*<<< orphan*/  stub22 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub23 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub3 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub4 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub5 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub6 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub7 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub8 (struct gf100_gr*) ; 
 int /*<<< orphan*/  stub9 (struct gf100_gr*) ; 

int
gf100_gr_init(struct gf100_gr *gr)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	int gpc, tpc, rop;

	if (gr->func->init_419bd8)
		gr->func->init_419bd8(gr);

	gr->func->init_gpc_mmu(gr);

	if (gr->fuc_sw_nonctx)
		gf100_gr_mmio(gr, gr->fuc_sw_nonctx);
	else
		gf100_gr_mmio(gr, gr->func->mmio);

	gf100_gr_wait_idle(gr);

	if (gr->func->init_r405a14)
		gr->func->init_r405a14(gr);

	if (gr->func->clkgate_pack)
		nvkm_therm_clkgate_init(device->therm, gr->func->clkgate_pack);

	if (gr->func->init_bios)
		gr->func->init_bios(gr);

	gr->func->init_vsc_stream_master(gr);
	gr->func->init_zcull(gr);
	gr->func->init_num_active_ltcs(gr);
	if (gr->func->init_rop_active_fbps)
		gr->func->init_rop_active_fbps(gr);
	if (gr->func->init_bios_2)
		gr->func->init_bios_2(gr);
	if (gr->func->init_swdx_pes_mask)
		gr->func->init_swdx_pes_mask(gr);

	nvkm_wr32(device, 0x400500, 0x00010001);

	nvkm_wr32(device, 0x400100, 0xffffffff);
	nvkm_wr32(device, 0x40013c, 0xffffffff);
	nvkm_wr32(device, 0x400124, 0x00000002);

	gr->func->init_fecs_exceptions(gr);
	if (gr->func->init_ds_hww_esr_2)
		gr->func->init_ds_hww_esr_2(gr);

	nvkm_wr32(device, 0x404000, 0xc0000000);
	nvkm_wr32(device, 0x404600, 0xc0000000);
	nvkm_wr32(device, 0x408030, 0xc0000000);

	if (gr->func->init_40601c)
		gr->func->init_40601c(gr);

	nvkm_wr32(device, 0x404490, 0xc0000000);
	nvkm_wr32(device, 0x406018, 0xc0000000);

	if (gr->func->init_sked_hww_esr)
		gr->func->init_sked_hww_esr(gr);

	nvkm_wr32(device, 0x405840, 0xc0000000);
	nvkm_wr32(device, 0x405844, 0x00ffffff);

	if (gr->func->init_419cc0)
		gr->func->init_419cc0(gr);
	if (gr->func->init_419eb4)
		gr->func->init_419eb4(gr);
	if (gr->func->init_419c9c)
		gr->func->init_419c9c(gr);

	if (gr->func->init_ppc_exceptions)
		gr->func->init_ppc_exceptions(gr);

	for (gpc = 0; gpc < gr->gpc_nr; gpc++) {
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0420), 0xc0000000);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0900), 0xc0000000);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x1028), 0xc0000000);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0824), 0xc0000000);
		for (tpc = 0; tpc < gr->tpc_nr[gpc]; tpc++) {
			nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x508), 0xffffffff);
			nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x50c), 0xffffffff);
			if (gr->func->init_tex_hww_esr)
				gr->func->init_tex_hww_esr(gr, gpc, tpc);
			nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x084), 0xc0000000);
			if (gr->func->init_504430)
				gr->func->init_504430(gr, gpc, tpc);
			gr->func->init_shader_exceptions(gr, gpc, tpc);
		}
		nvkm_wr32(device, GPC_UNIT(gpc, 0x2c90), 0xffffffff);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x2c94), 0xffffffff);
	}

	for (rop = 0; rop < gr->rop_nr; rop++) {
		nvkm_wr32(device, ROP_UNIT(rop, 0x144), 0x40000000);
		nvkm_wr32(device, ROP_UNIT(rop, 0x070), 0x40000000);
		nvkm_wr32(device, ROP_UNIT(rop, 0x204), 0xffffffff);
		nvkm_wr32(device, ROP_UNIT(rop, 0x208), 0xffffffff);
	}

	nvkm_wr32(device, 0x400108, 0xffffffff);
	nvkm_wr32(device, 0x400138, 0xffffffff);
	nvkm_wr32(device, 0x400118, 0xffffffff);
	nvkm_wr32(device, 0x400130, 0xffffffff);
	nvkm_wr32(device, 0x40011c, 0xffffffff);
	nvkm_wr32(device, 0x400134, 0xffffffff);

	if (gr->func->init_400054)
		gr->func->init_400054(gr);

	gf100_gr_zbc_init(gr);

	if (gr->func->init_4188a4)
		gr->func->init_4188a4(gr);

	return gf100_gr_init_ctxctl(gr);
}