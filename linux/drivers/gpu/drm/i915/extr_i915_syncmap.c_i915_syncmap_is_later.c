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
struct i915_syncmap {scalar_t__ prefix; int bitmap; int /*<<< orphan*/  height; struct i915_syncmap* parent; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 size_t __sync_branch_idx (struct i915_syncmap*,int /*<<< orphan*/ ) ; 
 scalar_t__ __sync_branch_prefix (struct i915_syncmap*,int /*<<< orphan*/ ) ; 
 struct i915_syncmap** __sync_child (struct i915_syncmap*) ; 
 unsigned int __sync_leaf_idx (struct i915_syncmap*,int /*<<< orphan*/ ) ; 
 scalar_t__ __sync_leaf_prefix (struct i915_syncmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __sync_seqno (struct i915_syncmap*) ; 
 scalar_t__ likely (int) ; 
 int seqno_later (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool i915_syncmap_is_later(struct i915_syncmap **root, u64 id, u32 seqno)
{
	struct i915_syncmap *p;
	unsigned int idx;

	p = *root;
	if (!p)
		return false;

	if (likely(__sync_leaf_prefix(p, id) == p->prefix))
		goto found;

	/* First climb the tree back to a parent branch */
	do {
		p = p->parent;
		if (!p)
			return false;

		if (__sync_branch_prefix(p, id) == p->prefix)
			break;
	} while (1);

	/* And then descend again until we find our leaf */
	do {
		if (!p->height)
			break;

		p = __sync_child(p)[__sync_branch_idx(p, id)];
		if (!p)
			return false;

		if (__sync_branch_prefix(p, id) != p->prefix)
			return false;
	} while (1);

	*root = p;
found:
	idx = __sync_leaf_idx(p, id);
	if (!(p->bitmap & BIT(idx)))
		return false;

	return seqno_later(__sync_seqno(p)[idx], seqno);
}