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
 int /*<<< orphan*/  gv100_disp_wimm ; 
 int gv100_disp_wimm_new_ (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nv50_disp*,int,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,struct nvkm_object**) ; 

int
gv100_disp_wimm_new(const struct nvkm_oclass *oclass, void *argv, u32 argc,
		    struct nv50_disp *disp, struct nvkm_object **pobject)
{
	return gv100_disp_wimm_new_(&gv100_disp_wimm, NULL, disp, 33,
				    oclass, argv, argc, pobject);
}