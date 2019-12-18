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
 int CONSOLE_LOGLEVEL_DEFAULT ; 
 int console_loglevel ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 

__attribute__((used)) static void sysrq_handle_loglevel(int key)
{
	int i;

	i = key - '0';
	console_loglevel = CONSOLE_LOGLEVEL_DEFAULT;
	pr_info("Loglevel set to %d\n", i);
	console_loglevel = i;
}