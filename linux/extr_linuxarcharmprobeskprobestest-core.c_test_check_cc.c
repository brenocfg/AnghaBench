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
 int ARM_OPCODE_CONDTEST_FAIL ; 
 int arm_check_condition (int,unsigned long) ; 

__attribute__((used)) static unsigned long test_check_cc(int cc, unsigned long cpsr)
{
	int ret = arm_check_condition(cc << 28, cpsr);

	return (ret != ARM_OPCODE_CONDTEST_FAIL);
}