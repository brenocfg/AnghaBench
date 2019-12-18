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
struct device {int dummy; } ;

/* Variables and functions */
#define  REG_INTSTAT 129 
#define  REG_TXSTAT 128 
 int mrf24j40_short_reg_writeable (struct device*,unsigned int) ; 

__attribute__((used)) static bool
mrf24j40_short_reg_readable(struct device *dev, unsigned int reg)
{
	bool rc;

	/* all writeable are also readable */
	rc = mrf24j40_short_reg_writeable(dev, reg);
	if (rc)
		return rc;

	/* readonly regs */
	switch (reg) {
	case REG_TXSTAT:
	case REG_INTSTAT:
		return true;
	default:
		return false;
	}
}