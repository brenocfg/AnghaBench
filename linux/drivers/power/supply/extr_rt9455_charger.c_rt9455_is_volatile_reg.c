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
#define  RT9455_REG_CTRL5 130 
#define  RT9455_REG_CTRL6 129 
#define  RT9455_REG_DEV_ID 128 

__attribute__((used)) static bool rt9455_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case RT9455_REG_DEV_ID:
	case RT9455_REG_CTRL5:
	case RT9455_REG_CTRL6:
		return false;
	default:
		return true;
	}
}