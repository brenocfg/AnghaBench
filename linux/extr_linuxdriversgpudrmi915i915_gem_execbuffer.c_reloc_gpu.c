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
typedef  int /*<<< orphan*/  u32 ;
struct reloc_cache {int rq_size; int /*<<< orphan*/ * rq_cmd; int /*<<< orphan*/  rq; } ;
struct i915_vma {int dummy; } ;
struct i915_execbuffer {int /*<<< orphan*/  engine; struct reloc_cache reloc_cache; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/ * ERR_PTR (int) ; 
 int EWOULDBLOCK ; 
 int PAGE_SIZE ; 
 int __reloc_gpu_alloc (struct i915_execbuffer*,struct i915_vma*,unsigned int) ; 
 scalar_t__ eb_use_cmdparser (struct i915_execbuffer*) ; 
 int /*<<< orphan*/  intel_engine_can_store_dword (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reloc_gpu_flush (struct reloc_cache*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32 *reloc_gpu(struct i915_execbuffer *eb,
		      struct i915_vma *vma,
		      unsigned int len)
{
	struct reloc_cache *cache = &eb->reloc_cache;
	u32 *cmd;

	if (cache->rq_size > PAGE_SIZE/sizeof(u32) - (len + 1))
		reloc_gpu_flush(cache);

	if (unlikely(!cache->rq)) {
		int err;

		/* If we need to copy for the cmdparser, we will stall anyway */
		if (eb_use_cmdparser(eb))
			return ERR_PTR(-EWOULDBLOCK);

		if (!intel_engine_can_store_dword(eb->engine))
			return ERR_PTR(-ENODEV);

		err = __reloc_gpu_alloc(eb, vma, len);
		if (unlikely(err))
			return ERR_PTR(err);
	}

	cmd = cache->rq_cmd + cache->rq_size;
	cache->rq_size += len;

	return cmd;
}