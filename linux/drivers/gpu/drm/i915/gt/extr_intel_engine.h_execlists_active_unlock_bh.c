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
struct intel_engine_execlists {int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  tasklet_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
execlists_active_unlock_bh(struct intel_engine_execlists *execlists)
{
	tasklet_unlock(&execlists->tasklet);
	local_bh_enable(); /* restore softirq, and kick ksoftirqd! */
}