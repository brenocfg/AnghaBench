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
 int BCM6328_TP1_DISABLED ; 
 int /*<<< orphan*/  REG_BCM6328_OTP ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm63xx_fixup_cpu1 () ; 
 scalar_t__ bmips_smp_enabled ; 

__attribute__((used)) static void bcm6328_quirks(void)
{
	/* Check CPU1 status in OTP (it is usually disabled) */
	if (__raw_readl(REG_BCM6328_OTP) & BCM6328_TP1_DISABLED)
		bmips_smp_enabled = 0;
	else
		bcm63xx_fixup_cpu1();
}