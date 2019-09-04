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
 unsigned int MAX44000_REG_STATUS ; 

__attribute__((used)) static bool max44000_precious_reg(struct device *dev, unsigned int reg)
{
	return reg == MAX44000_REG_STATUS;
}