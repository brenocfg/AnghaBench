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
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  read_sysreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * task_user_tls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpidr_el0 ; 

void tls_preserve_current_state(void)
{
	*task_user_tls(current) = read_sysreg(tpidr_el0);
}