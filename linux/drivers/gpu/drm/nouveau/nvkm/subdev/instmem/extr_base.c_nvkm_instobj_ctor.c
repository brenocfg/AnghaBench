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
struct nvkm_memory_func {int dummy; } ;
struct nvkm_instobj {int /*<<< orphan*/  head; int /*<<< orphan*/ * suspend; int /*<<< orphan*/  memory; } ;
struct nvkm_instmem {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_memory_ctor (struct nvkm_memory_func const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
nvkm_instobj_ctor(const struct nvkm_memory_func *func,
		  struct nvkm_instmem *imem, struct nvkm_instobj *iobj)
{
	nvkm_memory_ctor(func, &iobj->memory);
	iobj->suspend = NULL;
	spin_lock(&imem->lock);
	list_add_tail(&iobj->head, &imem->list);
	spin_unlock(&imem->lock);
}