#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_gr {TYPE_2__* func; } ;
struct nvkm_device {struct nvkm_gr* gr; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* inst ) (struct nvkm_gr*) ;} ;
struct TYPE_4__ {TYPE_1__ ctxsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nvkm_gr*) ; 

u32
nvkm_gr_ctxsw_inst(struct nvkm_device *device)
{
	struct nvkm_gr *gr = device->gr;
	if (gr && gr->func->ctxsw.inst)
		return gr->func->ctxsw.inst(gr);
	return 0;
}