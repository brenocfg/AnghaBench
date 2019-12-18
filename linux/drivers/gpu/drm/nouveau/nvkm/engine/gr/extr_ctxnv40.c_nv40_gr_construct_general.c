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
 int /*<<< orphan*/  cp_ctx (struct nvkm_grctx*,int,int) ; 
 int /*<<< orphan*/  gr_def (struct nvkm_grctx*,int,int) ; 
 scalar_t__ nv44_gr_class (struct nvkm_device*) ; 

__attribute__((used)) static void
nv40_gr_construct_general(struct nvkm_grctx *ctx)
{
	struct nvkm_device *device = ctx->device;
	int i;

	cp_ctx(ctx, 0x4000a4, 1);
	gr_def(ctx, 0x4000a4, 0x00000008);
	cp_ctx(ctx, 0x400144, 58);
	gr_def(ctx, 0x400144, 0x00000001);
	cp_ctx(ctx, 0x400314, 1);
	gr_def(ctx, 0x400314, 0x00000000);
	cp_ctx(ctx, 0x400400, 10);
	cp_ctx(ctx, 0x400480, 10);
	cp_ctx(ctx, 0x400500, 19);
	gr_def(ctx, 0x400514, 0x00040000);
	gr_def(ctx, 0x400524, 0x55555555);
	gr_def(ctx, 0x400528, 0x55555555);
	gr_def(ctx, 0x40052c, 0x55555555);
	gr_def(ctx, 0x400530, 0x55555555);
	cp_ctx(ctx, 0x400560, 6);
	gr_def(ctx, 0x400568, 0x0000ffff);
	gr_def(ctx, 0x40056c, 0x0000ffff);
	cp_ctx(ctx, 0x40057c, 5);
	cp_ctx(ctx, 0x400710, 3);
	gr_def(ctx, 0x400710, 0x20010001);
	gr_def(ctx, 0x400714, 0x0f73ef00);
	cp_ctx(ctx, 0x400724, 1);
	gr_def(ctx, 0x400724, 0x02008821);
	cp_ctx(ctx, 0x400770, 3);
	if (device->chipset == 0x40) {
		cp_ctx(ctx, 0x400814, 4);
		cp_ctx(ctx, 0x400828, 5);
		cp_ctx(ctx, 0x400840, 5);
		gr_def(ctx, 0x400850, 0x00000040);
		cp_ctx(ctx, 0x400858, 4);
		gr_def(ctx, 0x400858, 0x00000040);
		gr_def(ctx, 0x40085c, 0x00000040);
		gr_def(ctx, 0x400864, 0x80000000);
		cp_ctx(ctx, 0x40086c, 9);
		gr_def(ctx, 0x40086c, 0x80000000);
		gr_def(ctx, 0x400870, 0x80000000);
		gr_def(ctx, 0x400874, 0x80000000);
		gr_def(ctx, 0x400878, 0x80000000);
		gr_def(ctx, 0x400888, 0x00000040);
		gr_def(ctx, 0x40088c, 0x80000000);
		cp_ctx(ctx, 0x4009c0, 8);
		gr_def(ctx, 0x4009cc, 0x80000000);
		gr_def(ctx, 0x4009dc, 0x80000000);
	} else {
		cp_ctx(ctx, 0x400840, 20);
		if (nv44_gr_class(ctx->device)) {
			for (i = 0; i < 8; i++)
				gr_def(ctx, 0x400860 + (i * 4), 0x00000001);
		}
		gr_def(ctx, 0x400880, 0x00000040);
		gr_def(ctx, 0x400884, 0x00000040);
		gr_def(ctx, 0x400888, 0x00000040);
		cp_ctx(ctx, 0x400894, 11);
		gr_def(ctx, 0x400894, 0x00000040);
		if (!nv44_gr_class(ctx->device)) {
			for (i = 0; i < 8; i++)
				gr_def(ctx, 0x4008a0 + (i * 4), 0x80000000);
		}
		cp_ctx(ctx, 0x4008e0, 2);
		cp_ctx(ctx, 0x4008f8, 2);
		if (device->chipset == 0x4c ||
		    (device->chipset & 0xf0) == 0x60)
			cp_ctx(ctx, 0x4009f8, 1);
	}
	cp_ctx(ctx, 0x400a00, 73);
	gr_def(ctx, 0x400b0c, 0x0b0b0b0c);
	cp_ctx(ctx, 0x401000, 4);
	cp_ctx(ctx, 0x405004, 1);
	switch (device->chipset) {
	case 0x47:
	case 0x49:
	case 0x4b:
		cp_ctx(ctx, 0x403448, 1);
		gr_def(ctx, 0x403448, 0x00001010);
		break;
	default:
		cp_ctx(ctx, 0x403440, 1);
		switch (device->chipset) {
		case 0x40:
			gr_def(ctx, 0x403440, 0x00000010);
			break;
		case 0x44:
		case 0x46:
		case 0x4a:
			gr_def(ctx, 0x403440, 0x00003010);
			break;
		case 0x41:
		case 0x42:
		case 0x43:
		case 0x4c:
		case 0x4e:
		case 0x67:
		default:
			gr_def(ctx, 0x403440, 0x00001010);
			break;
		}
		break;
	}
}