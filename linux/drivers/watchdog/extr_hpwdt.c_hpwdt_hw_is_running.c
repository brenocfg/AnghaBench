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
 int /*<<< orphan*/  hpwdt_timer_con ; 
 int ioread8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpwdt_hw_is_running(void)
{
	return ioread8(hpwdt_timer_con) & 0x01;
}