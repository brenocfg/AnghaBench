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
struct cxl {int /*<<< orphan*/  contexts_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cxl_adapter_context_unlock(struct cxl *adapter)
{
	int val = atomic_cmpxchg(&adapter->contexts_num, -1, 0);

	/*
	 * contexts lock taken -> contexts_num == -1
	 * If not true then show a warning and force reset the lock.
	 * This will happen when context_unlock was requested without
	 * doing a context_lock.
	 */
	if (val != -1) {
		atomic_set(&adapter->contexts_num, 0);
		WARN(1, "Adapter context unlocked with %d active contexts",
		     val);
	}
}