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
#define  IS31FL319X_DATA_UPDATE 130 
#define  IS31FL319X_RESET 129 
#define  IS31FL319X_TIME_UPDATE 128 

__attribute__((used)) static bool is31fl319x_volatile_reg(struct device *dev, unsigned int reg)
{ /* volatile registers are not cached */
	switch (reg) {
	case IS31FL319X_DATA_UPDATE:
	case IS31FL319X_TIME_UPDATE:
	case IS31FL319X_RESET:
		return true; /* always write-through */
	default:
		return false;
	}
}