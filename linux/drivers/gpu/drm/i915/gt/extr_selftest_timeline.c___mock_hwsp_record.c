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
struct mock_hwsp_freelist {int /*<<< orphan*/  cachelines; int /*<<< orphan*/ * history; } ;
struct intel_timeline {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwsp_cacheline (struct intel_timeline*) ; 
 int /*<<< orphan*/  intel_timeline_put (struct intel_timeline*) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct intel_timeline* xchg (int /*<<< orphan*/ *,struct intel_timeline*) ; 

__attribute__((used)) static void __mock_hwsp_record(struct mock_hwsp_freelist *state,
			       unsigned int idx,
			       struct intel_timeline *tl)
{
	tl = xchg(&state->history[idx], tl);
	if (tl) {
		radix_tree_delete(&state->cachelines, hwsp_cacheline(tl));
		intel_timeline_put(tl);
	}
}