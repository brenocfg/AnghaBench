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
 int /*<<< orphan*/  stm32_exti_h_syscore_ops ; 
 int /*<<< orphan*/  unregister_syscore_ops (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stm32_exti_h_syscore_deinit(void)
{
	unregister_syscore_ops(&stm32_exti_h_syscore_ops);
}