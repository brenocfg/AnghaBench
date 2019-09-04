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
typedef  int /*<<< orphan*/  suspend_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  APMU_MOH_IDLE_CFG ; 
 unsigned int APMU_MOH_IDLE_CFG_MOH_PWRDWN ; 
 unsigned int APMU_MOH_IDLE_CFG_MOH_SRAM_PWRDWN ; 
 int /*<<< orphan*/  CIU_REG (int) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  ICU_INT_CONF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_PXA910_PMIC_INT ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  outer_disable () ; 
 int /*<<< orphan*/  outer_resume () ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pxa910_pm_enter(suspend_state_t state)
{
	unsigned int idle_cfg, reg = 0;

	/*pmic thread not completed,exit;otherwise system can't be waked up*/
	reg = __raw_readl(ICU_INT_CONF(IRQ_PXA910_PMIC_INT));
	if ((reg & 0x3) == 0)
		return -EAGAIN;

	idle_cfg = __raw_readl(APMU_MOH_IDLE_CFG);
	idle_cfg |= APMU_MOH_IDLE_CFG_MOH_PWRDWN
		| APMU_MOH_IDLE_CFG_MOH_SRAM_PWRDWN;
	__raw_writel(idle_cfg, APMU_MOH_IDLE_CFG);

	/* disable L2 */
	outer_disable();
	/* wait for l2 idle */
	while (!(readl(CIU_REG(0x8)) & (1 << 16)))
		udelay(1);

	cpu_do_idle();

	/* enable L2 */
	outer_resume();
	/* wait for l2 idle */
	while (!(readl(CIU_REG(0x8)) & (1 << 16)))
		udelay(1);

	idle_cfg = __raw_readl(APMU_MOH_IDLE_CFG);
	idle_cfg &= ~(APMU_MOH_IDLE_CFG_MOH_PWRDWN
		| APMU_MOH_IDLE_CFG_MOH_SRAM_PWRDWN);
	__raw_writel(idle_cfg, APMU_MOH_IDLE_CFG);

	return 0;
}