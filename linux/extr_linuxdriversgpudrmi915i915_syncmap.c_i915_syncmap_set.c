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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct i915_syncmap {scalar_t__ prefix; } ;

/* Variables and functions */
 scalar_t__ __sync_leaf_prefix (struct i915_syncmap*,int /*<<< orphan*/ ) ; 
 int __sync_set (struct i915_syncmap**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __sync_set_seqno (struct i915_syncmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

int i915_syncmap_set(struct i915_syncmap **root, u64 id, u32 seqno)
{
	struct i915_syncmap *p = *root;

	/*
	 * We expect to be called in sequence following is_later(id), which
	 * should have preloaded the root for us.
	 */
	if (likely(p && __sync_leaf_prefix(p, id) == p->prefix)) {
		__sync_set_seqno(p, id, seqno);
		return 0;
	}

	return __sync_set(root, id, seqno);
}