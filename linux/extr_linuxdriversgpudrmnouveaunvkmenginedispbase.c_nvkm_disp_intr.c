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
struct nvkm_engine {int dummy; } ;
struct nvkm_disp {TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* intr ) (struct nvkm_disp*) ;} ;

/* Variables and functions */
 struct nvkm_disp* nvkm_disp (struct nvkm_engine*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_disp*) ; 

__attribute__((used)) static void
nvkm_disp_intr(struct nvkm_engine *engine)
{
	struct nvkm_disp *disp = nvkm_disp(engine);
	disp->func->intr(disp);
}