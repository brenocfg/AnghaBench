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
 int /*<<< orphan*/  NOKIA_N800 ; 
 int /*<<< orphan*/  NOKIA_N810 ; 
 int /*<<< orphan*/  NOKIA_N810_WIMAX ; 
 int /*<<< orphan*/  board_caps ; 
 scalar_t__ of_machine_is_compatible (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void board_check_revision(void)
{
	if (of_machine_is_compatible("nokia,n800"))
		board_caps = NOKIA_N800;
	else if (of_machine_is_compatible("nokia,n810"))
		board_caps = NOKIA_N810;
	else if (of_machine_is_compatible("nokia,n810-wimax"))
		board_caps = NOKIA_N810_WIMAX;

	if (!board_caps)
		pr_err("Unknown board\n");
}