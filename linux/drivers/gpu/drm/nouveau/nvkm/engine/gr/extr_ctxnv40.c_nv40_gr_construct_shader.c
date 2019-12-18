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
struct nvkm_grctx {int ctxvals_pos; scalar_t__ mode; struct nvkm_device* device; struct nvkm_gpuobj* data; } ;
struct nvkm_gpuobj {int dummy; } ;
struct nvkm_device {int chipset; } ;

/* Variables and functions */
 scalar_t__ NVKM_GRCTX_VALS ; 
 int /*<<< orphan*/  cp_lsr (struct nvkm_grctx*,int) ; 
 int /*<<< orphan*/  cp_out (struct nvkm_grctx*,int) ; 
 int nv40_gr_vs_count (struct nvkm_device*) ; 
 scalar_t__ nv44_gr_class (struct nvkm_device*) ; 
 int /*<<< orphan*/  nvkm_wo32 (struct nvkm_gpuobj*,int,int) ; 

__attribute__((used)) static void
nv40_gr_construct_shader(struct nvkm_grctx *ctx)
{
	struct nvkm_device *device = ctx->device;
	struct nvkm_gpuobj *obj = ctx->data;
	int vs, vs_nr, vs_len, vs_nr_b0, vs_nr_b1, b0_offset, b1_offset;
	int offset, i;

	vs_nr    = nv40_gr_vs_count(ctx->device);
	vs_nr_b0 = 363;
	vs_nr_b1 = device->chipset == 0x40 ? 128 : 64;
	if (device->chipset == 0x40) {
		b0_offset = 0x2200/4; /* 33a0 */
		b1_offset = 0x55a0/4; /* 1500 */
		vs_len = 0x6aa0/4;
	} else
	if (device->chipset == 0x41 || device->chipset == 0x42) {
		b0_offset = 0x2200/4; /* 2200 */
		b1_offset = 0x4400/4; /* 0b00 */
		vs_len = 0x4f00/4;
	} else {
		b0_offset = 0x1d40/4; /* 2200 */
		b1_offset = 0x3f40/4; /* 0b00 : 0a40 */
		vs_len = nv44_gr_class(device) ? 0x4980/4 : 0x4a40/4;
	}

	cp_lsr(ctx, vs_len * vs_nr + 0x300/4);
	cp_out(ctx, nv44_gr_class(device) ? 0x800029 : 0x800041);

	offset = ctx->ctxvals_pos;
	ctx->ctxvals_pos += (0x0300/4 + (vs_nr * vs_len));

	if (ctx->mode != NVKM_GRCTX_VALS)
		return;

	offset += 0x0280/4;
	for (i = 0; i < 16; i++, offset += 2)
		nvkm_wo32(obj, offset * 4, 0x3f800000);

	for (vs = 0; vs < vs_nr; vs++, offset += vs_len) {
		for (i = 0; i < vs_nr_b0 * 6; i += 6)
			nvkm_wo32(obj, (offset + b0_offset + i) * 4, 0x00000001);
		for (i = 0; i < vs_nr_b1 * 4; i += 4)
			nvkm_wo32(obj, (offset + b1_offset + i) * 4, 0x3f800000);
	}
}