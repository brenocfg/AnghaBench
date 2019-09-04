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
typedef  int u32 ;
struct nvkm_grctx {int ctxvals_pos; int ctxvals_base; struct nvkm_device* device; } ;
struct nvkm_device {int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUSY ; 
 int /*<<< orphan*/  CP_SEEK_1 ; 
 int /*<<< orphan*/  CP_SET_XFER_POINTER ; 
 int /*<<< orphan*/  CP_XFER_1 ; 
 int /*<<< orphan*/  XFER ; 
 int /*<<< orphan*/  cp_lsr (struct nvkm_grctx*,int) ; 
 int /*<<< orphan*/  cp_out (struct nvkm_grctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_wait (struct nvkm_grctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_ccache (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_clipid (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_csched (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_dispatch (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_eng2d (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_m2mf (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_ropc (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_ropm1 (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_ropm2 (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_strmout (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_unk10xx (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_unk14xx (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_unk1cxx (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_unk24xx (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_unk34xx (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_vfetch (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_gene_zcull (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_xfer_tp (struct nvkm_grctx*) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static void
nv50_gr_construct_xfer1(struct nvkm_grctx *ctx)
{
	struct nvkm_device *device = ctx->device;
	int i;
	int offset;
	int size = 0;
	u32 units = nvkm_rd32(device, 0x1540);

	offset = (ctx->ctxvals_pos+0x3f)&~0x3f;
	ctx->ctxvals_base = offset;

	if (device->chipset < 0xa0) {
		/* Strand 0 */
		ctx->ctxvals_pos = offset;
		nv50_gr_construct_gene_dispatch(ctx);
		nv50_gr_construct_gene_m2mf(ctx);
		nv50_gr_construct_gene_unk24xx(ctx);
		nv50_gr_construct_gene_clipid(ctx);
		nv50_gr_construct_gene_zcull(ctx);
		if ((ctx->ctxvals_pos-offset)/8 > size)
			size = (ctx->ctxvals_pos-offset)/8;

		/* Strand 1 */
		ctx->ctxvals_pos = offset + 0x1;
		nv50_gr_construct_gene_vfetch(ctx);
		nv50_gr_construct_gene_eng2d(ctx);
		nv50_gr_construct_gene_csched(ctx);
		nv50_gr_construct_gene_ropm1(ctx);
		nv50_gr_construct_gene_ropm2(ctx);
		if ((ctx->ctxvals_pos-offset)/8 > size)
			size = (ctx->ctxvals_pos-offset)/8;

		/* Strand 2 */
		ctx->ctxvals_pos = offset + 0x2;
		nv50_gr_construct_gene_ccache(ctx);
		nv50_gr_construct_gene_unk1cxx(ctx);
		nv50_gr_construct_gene_strmout(ctx);
		nv50_gr_construct_gene_unk14xx(ctx);
		nv50_gr_construct_gene_unk10xx(ctx);
		nv50_gr_construct_gene_unk34xx(ctx);
		if ((ctx->ctxvals_pos-offset)/8 > size)
			size = (ctx->ctxvals_pos-offset)/8;

		/* Strand 3: per-ROP group state */
		ctx->ctxvals_pos = offset + 3;
		for (i = 0; i < 6; i++)
			if (units & (1 << (i + 16)))
				nv50_gr_construct_gene_ropc(ctx);
		if ((ctx->ctxvals_pos-offset)/8 > size)
			size = (ctx->ctxvals_pos-offset)/8;

		/* Strands 4-7: per-TP state */
		for (i = 0; i < 4; i++) {
			ctx->ctxvals_pos = offset + 4 + i;
			if (units & (1 << (2 * i)))
				nv50_gr_construct_xfer_tp(ctx);
			if (units & (1 << (2 * i + 1)))
				nv50_gr_construct_xfer_tp(ctx);
			if ((ctx->ctxvals_pos-offset)/8 > size)
				size = (ctx->ctxvals_pos-offset)/8;
		}
	} else {
		/* Strand 0 */
		ctx->ctxvals_pos = offset;
		nv50_gr_construct_gene_dispatch(ctx);
		nv50_gr_construct_gene_m2mf(ctx);
		nv50_gr_construct_gene_unk34xx(ctx);
		nv50_gr_construct_gene_csched(ctx);
		nv50_gr_construct_gene_unk1cxx(ctx);
		nv50_gr_construct_gene_strmout(ctx);
		if ((ctx->ctxvals_pos-offset)/8 > size)
			size = (ctx->ctxvals_pos-offset)/8;

		/* Strand 1 */
		ctx->ctxvals_pos = offset + 1;
		nv50_gr_construct_gene_unk10xx(ctx);
		if ((ctx->ctxvals_pos-offset)/8 > size)
			size = (ctx->ctxvals_pos-offset)/8;

		/* Strand 2 */
		ctx->ctxvals_pos = offset + 2;
		if (device->chipset == 0xa0)
			nv50_gr_construct_gene_unk14xx(ctx);
		nv50_gr_construct_gene_unk24xx(ctx);
		if ((ctx->ctxvals_pos-offset)/8 > size)
			size = (ctx->ctxvals_pos-offset)/8;

		/* Strand 3 */
		ctx->ctxvals_pos = offset + 3;
		nv50_gr_construct_gene_vfetch(ctx);
		if ((ctx->ctxvals_pos-offset)/8 > size)
			size = (ctx->ctxvals_pos-offset)/8;

		/* Strand 4 */
		ctx->ctxvals_pos = offset + 4;
		nv50_gr_construct_gene_ccache(ctx);
		if ((ctx->ctxvals_pos-offset)/8 > size)
			size = (ctx->ctxvals_pos-offset)/8;

		/* Strand 5 */
		ctx->ctxvals_pos = offset + 5;
		nv50_gr_construct_gene_ropm2(ctx);
		nv50_gr_construct_gene_ropm1(ctx);
		/* per-ROP context */
		for (i = 0; i < 8; i++)
			if (units & (1<<(i+16)))
				nv50_gr_construct_gene_ropc(ctx);
		if ((ctx->ctxvals_pos-offset)/8 > size)
			size = (ctx->ctxvals_pos-offset)/8;

		/* Strand 6 */
		ctx->ctxvals_pos = offset + 6;
		nv50_gr_construct_gene_zcull(ctx);
		nv50_gr_construct_gene_clipid(ctx);
		nv50_gr_construct_gene_eng2d(ctx);
		if (units & (1 << 0))
			nv50_gr_construct_xfer_tp(ctx);
		if (units & (1 << 1))
			nv50_gr_construct_xfer_tp(ctx);
		if (units & (1 << 2))
			nv50_gr_construct_xfer_tp(ctx);
		if (units & (1 << 3))
			nv50_gr_construct_xfer_tp(ctx);
		if ((ctx->ctxvals_pos-offset)/8 > size)
			size = (ctx->ctxvals_pos-offset)/8;

		/* Strand 7 */
		ctx->ctxvals_pos = offset + 7;
		if (device->chipset == 0xa0) {
			if (units & (1 << 4))
				nv50_gr_construct_xfer_tp(ctx);
			if (units & (1 << 5))
				nv50_gr_construct_xfer_tp(ctx);
			if (units & (1 << 6))
				nv50_gr_construct_xfer_tp(ctx);
			if (units & (1 << 7))
				nv50_gr_construct_xfer_tp(ctx);
			if (units & (1 << 8))
				nv50_gr_construct_xfer_tp(ctx);
			if (units & (1 << 9))
				nv50_gr_construct_xfer_tp(ctx);
		} else {
			nv50_gr_construct_gene_unk14xx(ctx);
		}
		if ((ctx->ctxvals_pos-offset)/8 > size)
			size = (ctx->ctxvals_pos-offset)/8;
	}

	ctx->ctxvals_pos = offset + size * 8;
	ctx->ctxvals_pos = (ctx->ctxvals_pos+0x3f)&~0x3f;
	cp_lsr (ctx, offset);
	cp_out (ctx, CP_SET_XFER_POINTER);
	cp_lsr (ctx, size);
	cp_out (ctx, CP_SEEK_1);
	cp_out (ctx, CP_XFER_1);
	cp_wait(ctx, XFER, BUSY);
}