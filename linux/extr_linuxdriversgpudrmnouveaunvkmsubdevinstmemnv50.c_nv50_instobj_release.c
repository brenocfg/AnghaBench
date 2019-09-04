#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nvkm_subdev {int /*<<< orphan*/  mutex; TYPE_2__* device; } ;
struct nvkm_memory {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ptrs; } ;
struct TYPE_10__ {TYPE_3__ memory; } ;
struct TYPE_11__ {int /*<<< orphan*/  next; } ;
struct nv50_instobj {TYPE_4__ base; TYPE_5__ lru; scalar_t__ map; int /*<<< orphan*/  maps; struct nv50_instmem* imem; } ;
struct TYPE_7__ {struct nvkm_subdev subdev; } ;
struct nv50_instmem {int /*<<< orphan*/  lru; TYPE_1__ base; } ;
struct TYPE_8__ {int /*<<< orphan*/  bar; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_5__*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nv50_instobj* nv50_instobj (struct nvkm_memory*) ; 
 int /*<<< orphan*/  nvkm_bar_flush (int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_dec_and_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
nv50_instobj_release(struct nvkm_memory *memory)
{
	struct nv50_instobj *iobj = nv50_instobj(memory);
	struct nv50_instmem *imem = iobj->imem;
	struct nvkm_subdev *subdev = &imem->base.subdev;

	wmb();
	nvkm_bar_flush(subdev->device->bar);

	if (refcount_dec_and_mutex_lock(&iobj->maps, &subdev->mutex)) {
		/* Add the now-unused mapping to the LRU instead of directly
		 * unmapping it here, in case we need to map it again later.
		 */
		if (likely(iobj->lru.next) && iobj->map) {
			BUG_ON(!list_empty(&iobj->lru));
			list_add_tail(&iobj->lru, &imem->lru);
		}

		/* Switch back to NULL accessors when last map is gone. */
		iobj->base.memory.ptrs = NULL;
		mutex_unlock(&subdev->mutex);
	}
}