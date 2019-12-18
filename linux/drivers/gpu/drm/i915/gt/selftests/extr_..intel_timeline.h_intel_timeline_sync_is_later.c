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
struct intel_timeline {int dummy; } ;
struct dma_fence {int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int __intel_timeline_sync_is_later (struct intel_timeline*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool intel_timeline_sync_is_later(struct intel_timeline *tl,
						const struct dma_fence *fence)
{
	return __intel_timeline_sync_is_later(tl, fence->context, fence->seqno);
}