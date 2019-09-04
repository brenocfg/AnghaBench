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
typedef  int /*<<< orphan*/  u32 ;
struct fimc_is {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCUCTL_REG_INTCR2 ; 
 int /*<<< orphan*/  MCUCTL_REG_INTSR2 ; 
 int /*<<< orphan*/  mcuctl_read (struct fimc_is*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcuctl_write (int /*<<< orphan*/ ,struct fimc_is*,int /*<<< orphan*/ ) ; 

void fimc_is_fw_clear_irq2(struct fimc_is *is)
{
	u32 cfg = mcuctl_read(is, MCUCTL_REG_INTSR2);
	mcuctl_write(cfg, is, MCUCTL_REG_INTCR2);
}