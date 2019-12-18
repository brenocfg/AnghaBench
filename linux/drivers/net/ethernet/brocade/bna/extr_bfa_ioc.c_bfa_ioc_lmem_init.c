#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pss_ctl_reg; } ;
struct bfa_ioc {TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PSS_LMEM_INIT_TIME ; 
 int __PSS_I2C_CLK_DIV (unsigned long) ; 
 int __PSS_LMEM_INIT_DONE ; 
 int __PSS_LMEM_INIT_EN ; 
 int __PSS_LMEM_RESET ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_lmem_init(struct bfa_ioc *ioc)
{
	u32	pss_ctl;
	int		i;
#define PSS_LMEM_INIT_TIME  10000

	pss_ctl = readl(ioc->ioc_regs.pss_ctl_reg);
	pss_ctl &= ~__PSS_LMEM_RESET;
	pss_ctl |= __PSS_LMEM_INIT_EN;

	/*
	 * i2c workaround 12.5khz clock
	 */
	pss_ctl |= __PSS_I2C_CLK_DIV(3UL);
	writel(pss_ctl, ioc->ioc_regs.pss_ctl_reg);

	/**
	 * wait for memory initialization to be complete
	 */
	i = 0;
	do {
		pss_ctl = readl(ioc->ioc_regs.pss_ctl_reg);
		i++;
	} while (!(pss_ctl & __PSS_LMEM_INIT_DONE) && (i < PSS_LMEM_INIT_TIME));

	/**
	 * If memory initialization is not successful, IOC timeout will catch
	 * such failures.
	 */
	BUG_ON(!(pss_ctl & __PSS_LMEM_INIT_DONE));

	pss_ctl &= ~(__PSS_LMEM_INIT_DONE | __PSS_LMEM_INIT_EN);
	writel(pss_ctl, ioc->ioc_regs.pss_ctl_reg);
}