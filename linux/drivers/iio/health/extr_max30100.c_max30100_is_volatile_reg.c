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
#define  MAX30100_REG_FIFO_DATA 135 
#define  MAX30100_REG_FIFO_OVR_CTR 134 
#define  MAX30100_REG_FIFO_RD_PTR 133 
#define  MAX30100_REG_FIFO_WR_PTR 132 
#define  MAX30100_REG_INT_STATUS 131 
#define  MAX30100_REG_MODE_CONFIG 130 
#define  MAX30100_REG_TEMP_FRACTION 129 
#define  MAX30100_REG_TEMP_INTEGER 128 

__attribute__((used)) static bool max30100_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case MAX30100_REG_INT_STATUS:
	case MAX30100_REG_MODE_CONFIG:
	case MAX30100_REG_FIFO_WR_PTR:
	case MAX30100_REG_FIFO_OVR_CTR:
	case MAX30100_REG_FIFO_RD_PTR:
	case MAX30100_REG_FIFO_DATA:
	case MAX30100_REG_TEMP_INTEGER:
	case MAX30100_REG_TEMP_FRACTION:
		return true;
	default:
		return false;
	}
}