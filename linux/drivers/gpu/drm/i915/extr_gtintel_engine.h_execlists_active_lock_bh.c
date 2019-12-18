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
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  tasklet_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
execlists_active_lock_bh(struct intel_engine_execlists *execlists)
{
	local_bh_disable(); /* prevent local softirq and lock recursion */
	tasklet_lock(&execlists->tasklet);
}