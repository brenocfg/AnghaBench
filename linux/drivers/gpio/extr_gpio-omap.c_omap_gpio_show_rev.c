#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct gpio_bank {scalar_t__ base; TYPE_1__* regs; } ;
struct TYPE_2__ {scalar_t__ revision; } ;

/* Variables and functions */
 scalar_t__ USHRT_MAX ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 
 int readw_relaxed (scalar_t__) ; 

__attribute__((used)) static void omap_gpio_show_rev(struct gpio_bank *bank)
{
	static bool called;
	u32 rev;

	if (called || bank->regs->revision == USHRT_MAX)
		return;

	rev = readw_relaxed(bank->base + bank->regs->revision);
	pr_info("OMAP GPIO hardware version %d.%d\n",
		(rev >> 4) & 0x0f, rev & 0x0f);

	called = true;
}