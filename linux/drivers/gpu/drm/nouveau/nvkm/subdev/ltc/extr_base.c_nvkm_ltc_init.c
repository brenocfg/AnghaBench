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
struct nvkm_subdev {int dummy; } ;
struct nvkm_ltc {int zbc_min; int zbc_max; TYPE_1__* func; int /*<<< orphan*/ * zbc_stencil; int /*<<< orphan*/ * zbc_depth; int /*<<< orphan*/ * zbc_color; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (struct nvkm_ltc*) ;int /*<<< orphan*/  (* zbc_clear_stencil ) (struct nvkm_ltc*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* zbc_clear_depth ) (struct nvkm_ltc*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* zbc_clear_color ) (struct nvkm_ltc*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct nvkm_ltc* nvkm_ltc (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_ltc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct nvkm_ltc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct nvkm_ltc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct nvkm_ltc*) ; 

__attribute__((used)) static int
nvkm_ltc_init(struct nvkm_subdev *subdev)
{
	struct nvkm_ltc *ltc = nvkm_ltc(subdev);
	int i;

	for (i = ltc->zbc_min; i <= ltc->zbc_max; i++) {
		ltc->func->zbc_clear_color(ltc, i, ltc->zbc_color[i]);
		ltc->func->zbc_clear_depth(ltc, i, ltc->zbc_depth[i]);
		if (ltc->func->zbc_clear_stencil)
			ltc->func->zbc_clear_stencil(ltc, i, ltc->zbc_stencil[i]);
	}

	ltc->func->init(ltc);
	return 0;
}