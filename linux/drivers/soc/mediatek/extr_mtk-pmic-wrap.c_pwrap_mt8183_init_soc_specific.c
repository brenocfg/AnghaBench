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
struct pmic_wrapper {TYPE_1__* slave; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dew_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWRAP_CRC_EN ; 
 size_t PWRAP_DEW_CRC_EN ; 
 int /*<<< orphan*/  PWRAP_EINT_STA0_ADR ; 
 int /*<<< orphan*/  PWRAP_INIT_DONE_MD32 ; 
 int /*<<< orphan*/  PWRAP_INIT_DONE_P2P ; 
 int /*<<< orphan*/  PWRAP_SIG_ADR ; 
 int /*<<< orphan*/  PWRAP_STAUPD_GRPEN ; 
 int /*<<< orphan*/  PWRAP_WACS_MD32_EN ; 
 int /*<<< orphan*/  PWRAP_WACS_P2P_EN ; 
 int /*<<< orphan*/  pwrap_write (struct pmic_wrapper*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pwrap_writel (struct pmic_wrapper*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pwrap_mt8183_init_soc_specific(struct pmic_wrapper *wrp)
{
	pwrap_writel(wrp, 0xf5, PWRAP_STAUPD_GRPEN);

	pwrap_write(wrp, wrp->slave->dew_regs[PWRAP_DEW_CRC_EN], 0x1);
	pwrap_writel(wrp, 1, PWRAP_CRC_EN);
	pwrap_writel(wrp, 0x416, PWRAP_SIG_ADR);
	pwrap_writel(wrp, 0x42e, PWRAP_EINT_STA0_ADR);

	pwrap_writel(wrp, 1, PWRAP_WACS_P2P_EN);
	pwrap_writel(wrp, 1, PWRAP_WACS_MD32_EN);
	pwrap_writel(wrp, 1, PWRAP_INIT_DONE_P2P);
	pwrap_writel(wrp, 1, PWRAP_INIT_DONE_MD32);

	return 0;
}