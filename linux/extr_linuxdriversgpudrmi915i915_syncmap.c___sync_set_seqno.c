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
struct i915_syncmap {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 unsigned int __sync_leaf_idx (struct i915_syncmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __sync_seqno (struct i915_syncmap*) ; 

__attribute__((used)) static inline void __sync_set_seqno(struct i915_syncmap *p, u64 id, u32 seqno)
{
	unsigned int idx = __sync_leaf_idx(p, id);

	p->bitmap |= BIT(idx);
	__sync_seqno(p)[idx] = seqno;
}