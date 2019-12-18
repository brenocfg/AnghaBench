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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  SP5100_IO_PM_DATA_REG ; 
 int /*<<< orphan*/  SP5100_IO_PM_INDEX_REG ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sp5100_tco_update_pm_reg8(u8 index, u8 reset, u8 set)
{
	u8 val;

	outb(index, SP5100_IO_PM_INDEX_REG);
	val = inb(SP5100_IO_PM_DATA_REG);
	val &= reset;
	val |= set;
	outb(val, SP5100_IO_PM_DATA_REG);
}