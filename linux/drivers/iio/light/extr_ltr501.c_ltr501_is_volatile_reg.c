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
#define  LTR501_ALS_DATA0 131 
#define  LTR501_ALS_DATA1 130 
#define  LTR501_ALS_PS_STATUS 129 
#define  LTR501_PS_DATA 128 

__attribute__((used)) static bool ltr501_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case LTR501_ALS_DATA1:
	case LTR501_ALS_DATA0:
	case LTR501_ALS_PS_STATUS:
	case LTR501_PS_DATA:
		return true;
	default:
		return false;
	}
}