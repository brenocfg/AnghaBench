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
struct nvkm_disp_func {int dummy; } ;
struct nvkm_disp {int /*<<< orphan*/  engine; int /*<<< orphan*/  conn; int /*<<< orphan*/  outp; int /*<<< orphan*/  ior; int /*<<< orphan*/  head; struct nvkm_disp_func const* func; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_disp ; 
 int nvkm_engine_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int,int /*<<< orphan*/ *) ; 

int
nvkm_disp_ctor(const struct nvkm_disp_func *func, struct nvkm_device *device,
	       int index, struct nvkm_disp *disp)
{
	disp->func = func;
	INIT_LIST_HEAD(&disp->head);
	INIT_LIST_HEAD(&disp->ior);
	INIT_LIST_HEAD(&disp->outp);
	INIT_LIST_HEAD(&disp->conn);
	return nvkm_engine_ctor(&nvkm_disp, device, index, true, &disp->engine);
}