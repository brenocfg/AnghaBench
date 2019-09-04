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
 int /*<<< orphan*/  __mcheck_cpu_init_clear_banks () ; 
 int /*<<< orphan*/  __mcheck_cpu_init_generic () ; 
 int /*<<< orphan*/  __mcheck_cpu_init_timer () ; 
 int /*<<< orphan*/  cpu_info ; 
 int /*<<< orphan*/  mce_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mce_cpu_restart(void *data)
{
	if (!mce_available(raw_cpu_ptr(&cpu_info)))
		return;
	__mcheck_cpu_init_generic();
	__mcheck_cpu_init_clear_banks();
	__mcheck_cpu_init_timer();
}