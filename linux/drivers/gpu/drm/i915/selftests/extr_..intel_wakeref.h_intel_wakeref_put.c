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
 int /*<<< orphan*/  INTEL_WAKEREF_BUG_ON (int) ; 
 int /*<<< orphan*/  __intel_wakeref_put_last (struct intel_wakeref*) ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void
intel_wakeref_put(struct intel_wakeref *wf)
{
	INTEL_WAKEREF_BUG_ON(atomic_read(&wf->count) <= 0);
	if (unlikely(!atomic_add_unless(&wf->count, -1, 1)))
		__intel_wakeref_put_last(wf);
}