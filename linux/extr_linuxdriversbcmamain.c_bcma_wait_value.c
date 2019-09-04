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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct bcma_device {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int bcma_read32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int jiffies ; 
 int /*<<< orphan*/  time_after_eq (int,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool bcma_wait_value(struct bcma_device *core, u16 reg, u32 mask, u32 value,
		     int timeout)
{
	unsigned long deadline = jiffies + timeout;
	u32 val;

	do {
		val = bcma_read32(core, reg);
		if ((val & mask) == value)
			return true;
		cpu_relax();
		udelay(10);
	} while (!time_after_eq(jiffies, deadline));

	bcma_warn(core->bus, "Timeout waiting for register 0x%04X!\n", reg);

	return false;
}