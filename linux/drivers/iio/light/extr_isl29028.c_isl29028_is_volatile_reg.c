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
#define  ISL29028_REG_ALSIR_L 131 
#define  ISL29028_REG_ALSIR_U 130 
#define  ISL29028_REG_INTERRUPT 129 
#define  ISL29028_REG_PROX_DATA 128 

__attribute__((used)) static bool isl29028_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case ISL29028_REG_INTERRUPT:
	case ISL29028_REG_PROX_DATA:
	case ISL29028_REG_ALSIR_L:
	case ISL29028_REG_ALSIR_U:
		return true;
	default:
		return false;
	}
}