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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_trace_list () ; 
 int /*<<< orphan*/  is_enabled () ; 
 int /*<<< orphan*/  kmmio_cleanup () ; 
 int /*<<< orphan*/  leave_uniprocessor () ; 
 int /*<<< orphan*/  mmiotrace_enabled ; 
 int /*<<< orphan*/  mmiotrace_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_lock ; 

void disable_mmiotrace(void)
{
	mutex_lock(&mmiotrace_mutex);
	if (!is_enabled())
		goto out;

	spin_lock_irq(&trace_lock);
	atomic_dec(&mmiotrace_enabled);
	BUG_ON(is_enabled());
	spin_unlock_irq(&trace_lock);

	clear_trace_list(); /* guarantees: no more kmmio callbacks */
	leave_uniprocessor();
	kmmio_cleanup();
	pr_info("disabled.\n");
out:
	mutex_unlock(&mmiotrace_mutex);
}