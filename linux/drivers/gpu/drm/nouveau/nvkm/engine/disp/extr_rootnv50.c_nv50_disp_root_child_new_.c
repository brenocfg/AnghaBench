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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_oclass {struct nv50_disp_user* priv; int /*<<< orphan*/  parent; } ;
struct nvkm_object {int dummy; } ;
struct nv50_disp_user {int (* ctor ) (struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,struct nv50_disp*,struct nvkm_object**) ;} ;
struct nv50_disp {int dummy; } ;
struct TYPE_2__ {struct nv50_disp* disp; } ;

/* Variables and functions */
 TYPE_1__* nv50_disp_root (int /*<<< orphan*/ ) ; 
 int stub1 (struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,struct nv50_disp*,struct nvkm_object**) ; 

__attribute__((used)) static int
nv50_disp_root_child_new_(const struct nvkm_oclass *oclass,
			  void *argv, u32 argc, struct nvkm_object **pobject)
{
	struct nv50_disp *disp = nv50_disp_root(oclass->parent)->disp;
	const struct nv50_disp_user *user = oclass->priv;
	return user->ctor(oclass, argv, argc, disp, pobject);
}