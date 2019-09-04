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
struct nvkm_disp {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct nv50_disp_func {int /*<<< orphan*/  uevent; int /*<<< orphan*/  super; } ;
struct nv50_disp {int /*<<< orphan*/  uevent; int /*<<< orphan*/  chan; int /*<<< orphan*/  supervisor; int /*<<< orphan*/  wq; struct nvkm_disp base; struct nv50_disp_func const* func; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 struct nv50_disp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv50_disp_ ; 
 int nvkm_disp_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_disp*) ; 
 int nvkm_event_init (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
nv50_disp_new_(const struct nv50_disp_func *func, struct nvkm_device *device,
	       int index, struct nvkm_disp **pdisp)
{
	struct nv50_disp *disp;
	int ret;

	if (!(disp = kzalloc(sizeof(*disp), GFP_KERNEL)))
		return -ENOMEM;
	disp->func = func;
	*pdisp = &disp->base;

	ret = nvkm_disp_ctor(&nv50_disp_, device, index, &disp->base);
	if (ret)
		return ret;

	disp->wq = create_singlethread_workqueue("nvkm-disp");
	if (!disp->wq)
		return -ENOMEM;

	INIT_WORK(&disp->supervisor, func->super);

	return nvkm_event_init(func->uevent, 1, ARRAY_SIZE(disp->chan),
			       &disp->uevent);
}