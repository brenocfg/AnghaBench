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
#define  ISL29018_REG_ADD_COMMAND1 132 
#define  ISL29018_REG_ADD_DATA_LSB 131 
#define  ISL29018_REG_ADD_DATA_MSB 130 
#define  ISL29018_REG_TEST 129 
#define  ISL29035_REG_DEVICE_ID 128 

__attribute__((used)) static bool isl29018_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case ISL29018_REG_ADD_DATA_LSB:
	case ISL29018_REG_ADD_DATA_MSB:
	case ISL29018_REG_ADD_COMMAND1:
	case ISL29018_REG_TEST:
	case ISL29035_REG_DEVICE_ID:
		return true;
	default:
		return false;
	}
}