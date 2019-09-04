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
 int /*<<< orphan*/  ipmi_user ; 
 int /*<<< orphan*/  ready ; 
 int /*<<< orphan*/  specific_poweroff_func (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipmi_poweroff_function(void)
{
	if (!ready)
		return;

	/* Use run-to-completion mode, since interrupts may be off. */
	specific_poweroff_func(ipmi_user);
}