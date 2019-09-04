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
typedef  int uint32_t ;
typedef  enum reboot_mode { ____Placeholder_reboot_mode } reboot_mode ;

/* Variables and functions */
 int /*<<< orphan*/  MSC0 ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spitz_poweroff () ; 

__attribute__((used)) static void spitz_restart(enum reboot_mode mode, const char *cmd)
{
	uint32_t msc0 = __raw_readl(MSC0);
	/* Bootloader magic for a reboot */
	if ((msc0 & 0xffff0000) == 0x7ff00000)
		__raw_writel((msc0 & 0xffff) | 0x7ee00000, MSC0);

	spitz_poweroff();
}