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
struct nvkm_instmem_func {int dummy; } ;
struct nvkm_instmem {int /*<<< orphan*/  boot; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; struct nvkm_instmem_func const* func; int /*<<< orphan*/  subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_instmem ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void
nvkm_instmem_ctor(const struct nvkm_instmem_func *func,
		  struct nvkm_device *device, int index,
		  struct nvkm_instmem *imem)
{
	nvkm_subdev_ctor(&nvkm_instmem, device, index, &imem->subdev);
	imem->func = func;
	spin_lock_init(&imem->lock);
	INIT_LIST_HEAD(&imem->list);
	INIT_LIST_HEAD(&imem->boot);
}