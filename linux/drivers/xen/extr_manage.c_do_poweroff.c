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
#define  SYSTEM_BOOTING 130 
#define  SYSTEM_RUNNING 129 
#define  SYSTEM_SCHEDULING 128 
 int /*<<< orphan*/  orderly_poweroff (int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int system_state ; 

__attribute__((used)) static void do_poweroff(void)
{
	switch (system_state) {
	case SYSTEM_BOOTING:
	case SYSTEM_SCHEDULING:
		orderly_poweroff(true);
		break;
	case SYSTEM_RUNNING:
		orderly_poweroff(false);
		break;
	default:
		/* Don't do it when we are halting/rebooting. */
		pr_info("Ignoring Xen toolstack shutdown.\n");
		break;
	}
}