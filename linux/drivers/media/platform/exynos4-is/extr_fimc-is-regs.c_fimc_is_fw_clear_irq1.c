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
struct fimc_is {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCUCTL_REG_INTCR1 ; 
 int /*<<< orphan*/  mcuctl_write (unsigned long,struct fimc_is*,int /*<<< orphan*/ ) ; 

void fimc_is_fw_clear_irq1(struct fimc_is *is, unsigned int nr)
{
	mcuctl_write(1UL << nr, is, MCUCTL_REG_INTCR1);
}