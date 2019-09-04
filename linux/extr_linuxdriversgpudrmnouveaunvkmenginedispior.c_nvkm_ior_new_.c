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
struct nvkm_ior_func {int dummy; } ;
struct nvkm_ior {int type; int id; int /*<<< orphan*/  head; int /*<<< orphan*/  name; struct nvkm_disp* disp; struct nvkm_ior_func const* func; } ;
struct nvkm_disp {int /*<<< orphan*/  ior; } ;
typedef  enum nvkm_ior_type { ____Placeholder_nvkm_ior_type } nvkm_ior_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IOR_DBG (struct nvkm_ior*,char*) ; 
 struct nvkm_ior* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char** nvkm_ior_name ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 

int
nvkm_ior_new_(const struct nvkm_ior_func *func, struct nvkm_disp *disp,
	      enum nvkm_ior_type type, int id)
{
	struct nvkm_ior *ior;
	if (!(ior = kzalloc(sizeof(*ior), GFP_KERNEL)))
		return -ENOMEM;
	ior->func = func;
	ior->disp = disp;
	ior->type = type;
	ior->id = id;
	snprintf(ior->name, sizeof(ior->name), "%s-%d",
		 nvkm_ior_name[ior->type], ior->id);
	list_add_tail(&ior->head, &disp->ior);
	IOR_DBG(ior, "ctor");
	return 0;
}