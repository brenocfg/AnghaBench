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
struct intel_timeline {int /*<<< orphan*/  sync; } ;

/* Variables and functions */
 int i915_syncmap_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __intel_timeline_sync_set(struct intel_timeline *tl,
					    u64 context, u32 seqno)
{
	return i915_syncmap_set(&tl->sync, context, seqno);
}