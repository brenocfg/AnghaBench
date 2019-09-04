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
 scalar_t__ WDT_EN ; 
 scalar_t__ WDT_SET ; 
 scalar_t__ WDT_TIMER ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  ls1x_halt () ; 
 scalar_t__ wdt_reg_base ; 

__attribute__((used)) static void ls1x_restart(char *command)
{
	__raw_writel(0x1, wdt_reg_base + WDT_EN);
	__raw_writel(0x1, wdt_reg_base + WDT_TIMER);
	__raw_writel(0x1, wdt_reg_base + WDT_SET);

	ls1x_halt();
}