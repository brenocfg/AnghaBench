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
 int /*<<< orphan*/  vga_arbiter_notify_clients () ; 
 int vga_arbiter_used ; 

__attribute__((used)) static void vga_check_first_use(void)
{
	/* we should inform all GPUs in the system that
	 * VGA arb has occurred and to try and disable resources
	 * if they can */
	if (!vga_arbiter_used) {
		vga_arbiter_used = true;
		vga_arbiter_notify_clients();
	}
}