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
 int /*<<< orphan*/  SBC8360_ENABLE ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int wd_multiplier ; 

__attribute__((used)) static void sbc8360_activate(void)
{
	/* Enable the watchdog */
	outb(0x0A, SBC8360_ENABLE);
	msleep_interruptible(100);
	outb(0x0B, SBC8360_ENABLE);
	msleep_interruptible(100);
	/* Set timeout multiplier */
	outb(wd_multiplier, SBC8360_ENABLE);
	msleep_interruptible(100);
	/* Nothing happens until first sbc8360_ping() */
}