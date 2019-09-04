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
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 unsigned long S3C64XX_PWRCFG_CFG_WFI_IDLE ; 
 unsigned long S3C64XX_PWRCFG_CFG_WFI_MASK ; 
 int /*<<< orphan*/  S3C64XX_PWR_CFG ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_do_idle () ; 

__attribute__((used)) static int s3c64xx_enter_idle(struct cpuidle_device *dev,
			      struct cpuidle_driver *drv,
			      int index)
{
	unsigned long tmp;

	/* Setup PWRCFG to enter idle mode */
	tmp = __raw_readl(S3C64XX_PWR_CFG);
	tmp &= ~S3C64XX_PWRCFG_CFG_WFI_MASK;
	tmp |= S3C64XX_PWRCFG_CFG_WFI_IDLE;
	__raw_writel(tmp, S3C64XX_PWR_CFG);

	cpu_do_idle();

	return index;
}