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
struct nvkm_gr_func {int dummy; } ;
struct nvkm_gr {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct nv10_gr {struct nvkm_gr base; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nv10_gr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvkm_gr_ctor (struct nvkm_gr_func const*,struct nvkm_device*,int,int,struct nvkm_gr*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
nv10_gr_new_(const struct nvkm_gr_func *func, struct nvkm_device *device,
	     int index, struct nvkm_gr **pgr)
{
	struct nv10_gr *gr;

	if (!(gr = kzalloc(sizeof(*gr), GFP_KERNEL)))
		return -ENOMEM;
	spin_lock_init(&gr->lock);
	*pgr = &gr->base;

	return nvkm_gr_ctor(func, device, index, true, &gr->base);
}