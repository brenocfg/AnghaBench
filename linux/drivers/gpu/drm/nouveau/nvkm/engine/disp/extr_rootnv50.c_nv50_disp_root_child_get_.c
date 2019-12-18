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
struct nvkm_oclass {int /*<<< orphan*/  ctor; TYPE_2__* priv; int /*<<< orphan*/  base; } ;
struct nvkm_object {int dummy; } ;
struct nv50_disp_root {TYPE_1__* func; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; scalar_t__ ctor; } ;
struct TYPE_3__ {TYPE_2__* user; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nv50_disp_root* nv50_disp_root (struct nvkm_object*) ; 
 int /*<<< orphan*/  nv50_disp_root_child_new_ ; 

__attribute__((used)) static int
nv50_disp_root_child_get_(struct nvkm_object *object, int index,
			  struct nvkm_oclass *sclass)
{
	struct nv50_disp_root *root = nv50_disp_root(object);

	if (root->func->user[index].ctor) {
		sclass->base = root->func->user[index].base;
		sclass->priv = root->func->user + index;
		sclass->ctor = nv50_disp_root_child_new_;
		return 0;
	}

	return -EINVAL;
}