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
#define  RG_IRQ_STATUS 134 
#define  RG_MAN_ID_0 133 
#define  RG_MAN_ID_1 132 
#define  RG_PART_NUM 131 
#define  RG_PHY_RSSI 130 
#define  RG_TRX_STATUS 129 
#define  RG_VERSION_NUM 128 
 int at86rf230_reg_writeable (struct device*,unsigned int) ; 

__attribute__((used)) static bool
at86rf230_reg_readable(struct device *dev, unsigned int reg)
{
	bool rc;

	/* all writeable are also readable */
	rc = at86rf230_reg_writeable(dev, reg);
	if (rc)
		return rc;

	/* readonly regs */
	switch (reg) {
	case RG_TRX_STATUS:
	case RG_PHY_RSSI:
	case RG_IRQ_STATUS:
	case RG_PART_NUM:
	case RG_VERSION_NUM:
	case RG_MAN_ID_1:
	case RG_MAN_ID_0:
		return true;
	default:
		return false;
	}
}