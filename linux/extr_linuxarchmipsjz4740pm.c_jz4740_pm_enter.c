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
typedef  int /*<<< orphan*/  suspend_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  JZ4740_WAIT_MODE_IDLE ; 
 int /*<<< orphan*/  JZ4740_WAIT_MODE_SLEEP ; 
 int /*<<< orphan*/  jz4740_clock_resume () ; 
 int /*<<< orphan*/  jz4740_clock_set_wait_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4740_clock_suspend () ; 

__attribute__((used)) static int jz4740_pm_enter(suspend_state_t state)
{
	jz4740_clock_suspend();

	jz4740_clock_set_wait_mode(JZ4740_WAIT_MODE_SLEEP);

	__asm__(".set\tmips3\n\t"
		"wait\n\t"
		".set\tmips0");

	jz4740_clock_set_wait_mode(JZ4740_WAIT_MODE_IDLE);

	jz4740_clock_resume();

	return 0;
}