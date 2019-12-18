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
#define  ADS1015_CFG_REG 130 
#define  ADS1015_HI_THRESH_REG 129 
#define  ADS1015_LO_THRESH_REG 128 

__attribute__((used)) static bool ads1015_is_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case ADS1015_CFG_REG:
	case ADS1015_LO_THRESH_REG:
	case ADS1015_HI_THRESH_REG:
		return true;
	default:
		return false;
	}
}