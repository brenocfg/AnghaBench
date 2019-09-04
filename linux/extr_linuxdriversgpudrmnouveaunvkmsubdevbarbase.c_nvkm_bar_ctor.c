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
struct nvkm_device {int dummy; } ;
struct nvkm_bar_func {int dummy; } ;
struct nvkm_bar {int /*<<< orphan*/  lock; struct nvkm_bar_func const* func; int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_bar ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void
nvkm_bar_ctor(const struct nvkm_bar_func *func, struct nvkm_device *device,
	      int index, struct nvkm_bar *bar)
{
	nvkm_subdev_ctor(&nvkm_bar, device, index, &bar->subdev);
	bar->func = func;
	spin_lock_init(&bar->lock);
}