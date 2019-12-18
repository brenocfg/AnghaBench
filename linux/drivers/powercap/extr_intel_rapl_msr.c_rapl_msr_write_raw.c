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
struct reg_action {int err; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  rapl_msr_update_func ; 
 int smp_call_function_single (int,int /*<<< orphan*/ ,struct reg_action*,int) ; 

__attribute__((used)) static int rapl_msr_write_raw(int cpu, struct reg_action *ra)
{
	int ret;

	ret = smp_call_function_single(cpu, rapl_msr_update_func, ra, 1);
	if (WARN_ON_ONCE(ret))
		return ret;

	return ra->err;
}