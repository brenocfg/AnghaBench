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
 int /*<<< orphan*/  INTGR0_INTGD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCUCTL_REG_INTGR0 ; 
 int /*<<< orphan*/  mcuctl_write (int /*<<< orphan*/ ,struct fimc_is*,int /*<<< orphan*/ ) ; 

void fimc_is_hw_set_intgr0_gd0(struct fimc_is *is)
{
	mcuctl_write(INTGR0_INTGD(0), is, MCUCTL_REG_INTGR0);
}