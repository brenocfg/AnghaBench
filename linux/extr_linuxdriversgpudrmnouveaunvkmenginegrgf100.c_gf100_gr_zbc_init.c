#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_ltc {int zbc_min; int zbc_max; } ;
struct TYPE_9__ {TYPE_1__* device; } ;
struct TYPE_10__ {TYPE_2__ subdev; } ;
struct TYPE_11__ {TYPE_3__ engine; } ;
struct gf100_gr {TYPE_7__* func; TYPE_5__* zbc_color; TYPE_4__ base; } ;
struct TYPE_14__ {TYPE_6__* zbc; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* clear_stencil ) (struct gf100_gr*,int) ;int /*<<< orphan*/  (* clear_depth ) (struct gf100_gr*,int) ;int /*<<< orphan*/  (* clear_color ) (struct gf100_gr*,int) ;int /*<<< orphan*/  (* stencil_get ) (struct gf100_gr*,int,int,int) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  format; } ;
struct TYPE_8__ {struct nvkm_ltc* ltc; } ;

/* Variables and functions */
 int /*<<< orphan*/  gf100_gr_zbc_color_get (struct gf100_gr*,int,int const*,int const*) ; 
 int /*<<< orphan*/  gf100_gr_zbc_depth_get (struct gf100_gr*,int,int,int) ; 
 int /*<<< orphan*/  stub1 (struct gf100_gr*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct gf100_gr*,int,int,int) ; 
 int /*<<< orphan*/  stub3 (struct gf100_gr*,int,int,int) ; 
 int /*<<< orphan*/  stub4 (struct gf100_gr*,int) ; 
 int /*<<< orphan*/  stub5 (struct gf100_gr*,int) ; 
 int /*<<< orphan*/  stub6 (struct gf100_gr*,int) ; 

void
gf100_gr_zbc_init(struct gf100_gr *gr)
{
	const u32  zero[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000,
			      0x00000000, 0x00000000, 0x00000000, 0x00000000 };
	const u32   one[] = { 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000,
			      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff };
	const u32 f32_0[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000,
			      0x00000000, 0x00000000, 0x00000000, 0x00000000 };
	const u32 f32_1[] = { 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000,
			      0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000 };
	struct nvkm_ltc *ltc = gr->base.engine.subdev.device->ltc;
	int index, c = ltc->zbc_min, d = ltc->zbc_min, s = ltc->zbc_min;

	if (!gr->zbc_color[0].format) {
		gf100_gr_zbc_color_get(gr, 1,  & zero[0],   &zero[4]); c++;
		gf100_gr_zbc_color_get(gr, 2,  &  one[0],    &one[4]); c++;
		gf100_gr_zbc_color_get(gr, 4,  &f32_0[0],  &f32_0[4]); c++;
		gf100_gr_zbc_color_get(gr, 4,  &f32_1[0],  &f32_1[4]); c++;
		gf100_gr_zbc_depth_get(gr, 1, 0x00000000, 0x00000000); d++;
		gf100_gr_zbc_depth_get(gr, 1, 0x3f800000, 0x3f800000); d++;
		if (gr->func->zbc->stencil_get) {
			gr->func->zbc->stencil_get(gr, 1, 0x00, 0x00); s++;
			gr->func->zbc->stencil_get(gr, 1, 0x01, 0x01); s++;
			gr->func->zbc->stencil_get(gr, 1, 0xff, 0xff); s++;
		}
	}

	for (index = c; index <= ltc->zbc_max; index++)
		gr->func->zbc->clear_color(gr, index);
	for (index = d; index <= ltc->zbc_max; index++)
		gr->func->zbc->clear_depth(gr, index);

	if (gr->func->zbc->clear_stencil) {
		for (index = s; index <= ltc->zbc_max; index++)
			gr->func->zbc->clear_stencil(gr, index);
	}
}