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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_oclass {int dummy; } ;
struct nvkm_object {int dummy; } ;
struct nv50_disp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv50_disp_dmac_func ; 
 int /*<<< orphan*/  nv50_disp_ovly_mthd ; 
 int nv50_disp_ovly_new_ (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nv50_disp*,int,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,struct nvkm_object**) ; 

int
nv50_disp_ovly_new(const struct nvkm_oclass *oclass, void *argv, u32 argc,
		   struct nv50_disp *disp, struct nvkm_object **pobject)
{
	return nv50_disp_ovly_new_(&nv50_disp_dmac_func, &nv50_disp_ovly_mthd,
				   disp, 3, oclass, argv, argc, pobject);
}