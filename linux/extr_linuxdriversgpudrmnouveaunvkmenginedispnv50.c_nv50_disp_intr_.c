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
struct nvkm_disp {int dummy; } ;
struct nv50_disp {TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* intr ) (struct nv50_disp*) ;} ;

/* Variables and functions */
 struct nv50_disp* nv50_disp (struct nvkm_disp*) ; 
 int /*<<< orphan*/  stub1 (struct nv50_disp*) ; 

__attribute__((used)) static void
nv50_disp_intr_(struct nvkm_disp *base)
{
	struct nv50_disp *disp = nv50_disp(base);
	disp->func->intr(disp);
}