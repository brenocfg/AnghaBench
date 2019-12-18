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
#define  MMC35240_REG_ID 135 
#define  MMC35240_REG_STATUS 134 
#define  MMC35240_REG_XOUT_H 133 
#define  MMC35240_REG_XOUT_L 132 
#define  MMC35240_REG_YOUT_H 131 
#define  MMC35240_REG_YOUT_L 130 
#define  MMC35240_REG_ZOUT_H 129 
#define  MMC35240_REG_ZOUT_L 128 

__attribute__((used)) static bool mmc35240_is_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case MMC35240_REG_XOUT_L:
	case MMC35240_REG_XOUT_H:
	case MMC35240_REG_YOUT_L:
	case MMC35240_REG_YOUT_H:
	case MMC35240_REG_ZOUT_L:
	case MMC35240_REG_ZOUT_H:
	case MMC35240_REG_STATUS:
	case MMC35240_REG_ID:
		return true;
	default:
		return false;
	}
}