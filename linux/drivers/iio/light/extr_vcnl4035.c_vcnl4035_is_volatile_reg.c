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
#define  VCNL4035_ALS_CONF 129 
#define  VCNL4035_DEV_ID 128 

__attribute__((used)) static bool vcnl4035_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case VCNL4035_ALS_CONF:
	case VCNL4035_DEV_ID:
		return false;
	default:
		return true;
	}
}