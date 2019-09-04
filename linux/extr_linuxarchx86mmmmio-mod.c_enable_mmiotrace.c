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
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enter_uniprocessor () ; 
 scalar_t__ is_enabled () ; 
 int /*<<< orphan*/  kmmio_init () ; 
 int /*<<< orphan*/  mmiotrace_enabled ; 
 int /*<<< orphan*/  mmiotrace_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nommiotrace ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_lock ; 

void enable_mmiotrace(void)
{
	mutex_lock(&mmiotrace_mutex);
	if (is_enabled())
		goto out;

	if (nommiotrace)
		pr_info("MMIO tracing disabled.\n");
	kmmio_init();
	enter_uniprocessor();
	spin_lock_irq(&trace_lock);
	atomic_inc(&mmiotrace_enabled);
	spin_unlock_irq(&trace_lock);
	pr_info("enabled.\n");
out:
	mutex_unlock(&mmiotrace_mutex);
}