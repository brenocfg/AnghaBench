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
 unsigned int DP0_LTSTAT ; 
 unsigned int DP0_SNKLTCHGREQ ; 
 unsigned int TC_IDREG ; 

__attribute__((used)) static bool tc_writeable_reg(struct device *dev, unsigned int reg)
{
	return (reg != TC_IDREG) &&
	       (reg != DP0_LTSTAT) &&
	       (reg != DP0_SNKLTCHGREQ);
}