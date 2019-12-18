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
struct nvkm_grctx {struct nvkm_device* device; } ;
struct nvkm_device {int chipset; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv50_gr_construct_xfer_tex (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_xfer_tprop (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_xfer_unk84xx (struct nvkm_grctx*) ; 
 int /*<<< orphan*/  nv50_gr_construct_xfer_unk8cxx (struct nvkm_grctx*) ; 

__attribute__((used)) static void
nv50_gr_construct_xfer_tp(struct nvkm_grctx *ctx)
{
	struct nvkm_device *device = ctx->device;
	if (device->chipset < 0xa0) {
		nv50_gr_construct_xfer_unk84xx(ctx);
		nv50_gr_construct_xfer_tprop(ctx);
		nv50_gr_construct_xfer_tex(ctx);
		nv50_gr_construct_xfer_unk8cxx(ctx);
	} else {
		nv50_gr_construct_xfer_tex(ctx);
		nv50_gr_construct_xfer_tprop(ctx);
		nv50_gr_construct_xfer_unk8cxx(ctx);
		nv50_gr_construct_xfer_unk84xx(ctx);
	}
}