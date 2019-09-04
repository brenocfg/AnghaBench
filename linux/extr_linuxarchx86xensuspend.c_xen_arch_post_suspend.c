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
 int /*<<< orphan*/  xen_hvm_post_suspend (int) ; 
 scalar_t__ xen_pv_domain () ; 
 int /*<<< orphan*/  xen_pv_post_suspend (int) ; 
 int /*<<< orphan*/  xen_restore_time_memory_area () ; 

void xen_arch_post_suspend(int cancelled)
{
	if (xen_pv_domain())
		xen_pv_post_suspend(cancelled);
	else
		xen_hvm_post_suspend(cancelled);

	xen_restore_time_memory_area();
}