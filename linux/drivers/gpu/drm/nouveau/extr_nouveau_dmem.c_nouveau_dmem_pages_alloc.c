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
struct nouveau_drm {TYPE_1__* dmem; } ;
struct nouveau_dmem_chunk {unsigned long pfn_first; int /*<<< orphan*/  lock; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  callocated; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 unsigned long DMEM_CHUNK_NPAGES ; 
 unsigned long find_first_zero_bit (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long find_next_zero_bit (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  memset (unsigned long*,int,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nouveau_dmem_chunk_alloc (struct nouveau_drm*) ; 
 struct nouveau_dmem_chunk* nouveau_dmem_chunk_first_free_locked (struct nouveau_drm*) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nouveau_dmem_pages_alloc(struct nouveau_drm *drm,
			 unsigned long npages,
			 unsigned long *pages)
{
	struct nouveau_dmem_chunk *chunk;
	unsigned long c;
	int ret;

	memset(pages, 0xff, npages * sizeof(*pages));

	mutex_lock(&drm->dmem->mutex);
	for (c = 0; c < npages;) {
		unsigned long i;

		chunk = nouveau_dmem_chunk_first_free_locked(drm);
		if (chunk == NULL) {
			mutex_unlock(&drm->dmem->mutex);
			ret = nouveau_dmem_chunk_alloc(drm);
			if (ret) {
				if (c)
					return 0;
				return ret;
			}
			mutex_lock(&drm->dmem->mutex);
			continue;
		}

		spin_lock(&chunk->lock);
		i = find_first_zero_bit(chunk->bitmap, DMEM_CHUNK_NPAGES);
		while (i < DMEM_CHUNK_NPAGES && c < npages) {
			pages[c] = chunk->pfn_first + i;
			set_bit(i, chunk->bitmap);
			chunk->callocated++;
			c++;

			i = find_next_zero_bit(chunk->bitmap,
					DMEM_CHUNK_NPAGES, i);
		}
		spin_unlock(&chunk->lock);
	}
	mutex_unlock(&drm->dmem->mutex);

	return 0;
}