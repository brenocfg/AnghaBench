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
struct intel_wakeref {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int __intel_wakeref_get_first (struct intel_wakeref*) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int
intel_wakeref_get(struct intel_wakeref *wf)
{
	if (unlikely(!atomic_inc_not_zero(&wf->count)))
		return __intel_wakeref_get_first(wf);

	return 0;
}