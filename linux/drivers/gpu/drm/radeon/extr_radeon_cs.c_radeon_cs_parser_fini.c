#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* fence; } ;
struct radeon_cs_parser {unsigned int nrelocs; unsigned int nchunks; TYPE_3__ const_ib; int /*<<< orphan*/  rdev; TYPE_3__ ib; TYPE_5__* chunks_array; TYPE_5__* chunks; TYPE_4__* vm_bos; TYPE_4__* relocs; TYPE_5__* track; int /*<<< orphan*/  validated; int /*<<< orphan*/  ticket; } ;
struct TYPE_7__ {int /*<<< orphan*/  base; } ;
struct radeon_bo {TYPE_2__ tbo; } ;
struct TYPE_10__ {TYPE_4__* kdata; } ;
struct TYPE_9__ {struct radeon_bo* robj; } ;
struct TYPE_6__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_size_smaller_first ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 int /*<<< orphan*/  kvfree (TYPE_4__*) ; 
 int /*<<< orphan*/  list_sort (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ib_free (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ttm_eu_backoff_reservation (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_eu_fence_buffer_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void radeon_cs_parser_fini(struct radeon_cs_parser *parser, int error, bool backoff)
{
	unsigned i;

	if (!error) {
		/* Sort the buffer list from the smallest to largest buffer,
		 * which affects the order of buffers in the LRU list.
		 * This assures that the smallest buffers are added first
		 * to the LRU list, so they are likely to be later evicted
		 * first, instead of large buffers whose eviction is more
		 * expensive.
		 *
		 * This slightly lowers the number of bytes moved by TTM
		 * per frame under memory pressure.
		 */
		list_sort(NULL, &parser->validated, cmp_size_smaller_first);

		ttm_eu_fence_buffer_objects(&parser->ticket,
					    &parser->validated,
					    &parser->ib.fence->base);
	} else if (backoff) {
		ttm_eu_backoff_reservation(&parser->ticket,
					   &parser->validated);
	}

	if (parser->relocs != NULL) {
		for (i = 0; i < parser->nrelocs; i++) {
			struct radeon_bo *bo = parser->relocs[i].robj;
			if (bo == NULL)
				continue;

			drm_gem_object_put_unlocked(&bo->tbo.base);
		}
	}
	kfree(parser->track);
	kvfree(parser->relocs);
	kvfree(parser->vm_bos);
	for (i = 0; i < parser->nchunks; i++)
		kvfree(parser->chunks[i].kdata);
	kfree(parser->chunks);
	kfree(parser->chunks_array);
	radeon_ib_free(parser->rdev, &parser->ib);
	radeon_ib_free(parser->rdev, &parser->const_ib);
}