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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  APMU_MC_HW_SLP_TYPE ; 
 int /*<<< orphan*/  APMU_MOH_IDLE_CFG ; 
 int APMU_MOH_IDLE_CFG_MOH_DIS_MC_SW_REQ ; 
 int APMU_MOH_IDLE_CFG_MOH_IDLE ; 
 int APMU_MOH_IDLE_CFG_MOH_L2_PWR_SW (int) ; 
 int APMU_MOH_IDLE_CFG_MOH_MC_WAKE_EN ; 
 int APMU_MOH_IDLE_CFG_MOH_PWRDWN ; 
 int APMU_MOH_IDLE_CFG_MOH_PWR_SW (int) ; 
 int /*<<< orphan*/  MPMU_APCR ; 
 int MPMU_APCR_APBSD ; 
 int MPMU_APCR_AXISD ; 
 int MPMU_APCR_BBSD ; 
 int MPMU_APCR_DDRCORSD ; 
 int MPMU_APCR_DSPSD ; 
 int MPMU_APCR_DTCMSD ; 
 int MPMU_APCR_MSASLPEN ; 
 int MPMU_APCR_SLPEN ; 
 int MPMU_APCR_STBYEN ; 
 int MPMU_APCR_VCTCXOSD ; 
#define  POWER_MODE_APPS_IDLE 133 
#define  POWER_MODE_APPS_SLEEP 132 
#define  POWER_MODE_CORE_EXTIDLE 131 
#define  POWER_MODE_CORE_INTIDLE 130 
#define  POWER_MODE_SYS_SLEEP 129 
#define  POWER_MODE_UDR 128 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

void pxa910_pm_enter_lowpower_mode(int state)
{
	uint32_t idle_cfg, apcr;

	idle_cfg = __raw_readl(APMU_MOH_IDLE_CFG);
	apcr = __raw_readl(MPMU_APCR);

	apcr &= ~(MPMU_APCR_DDRCORSD | MPMU_APCR_APBSD | MPMU_APCR_AXISD
		| MPMU_APCR_VCTCXOSD | MPMU_APCR_STBYEN);
	idle_cfg &= ~(APMU_MOH_IDLE_CFG_MOH_IDLE
		| APMU_MOH_IDLE_CFG_MOH_PWRDWN);

	switch (state) {
	case POWER_MODE_UDR:
		/* only shutdown APB in UDR */
		apcr |= MPMU_APCR_STBYEN | MPMU_APCR_APBSD;
		/* fall through */
	case POWER_MODE_SYS_SLEEP:
		apcr |= MPMU_APCR_SLPEN;		/* set the SLPEN bit */
		apcr |= MPMU_APCR_VCTCXOSD;		/* set VCTCXOSD */
		/* fall through */
	case POWER_MODE_APPS_SLEEP:
		apcr |= MPMU_APCR_DDRCORSD;		/* set DDRCORSD */
		/* fall through */
	case POWER_MODE_APPS_IDLE:
		apcr |= MPMU_APCR_AXISD;		/* set AXISDD bit */
		/* fall through */
	case POWER_MODE_CORE_EXTIDLE:
		idle_cfg |= APMU_MOH_IDLE_CFG_MOH_IDLE;
		idle_cfg |= APMU_MOH_IDLE_CFG_MOH_PWRDWN;
		idle_cfg |= APMU_MOH_IDLE_CFG_MOH_PWR_SW(3)
			| APMU_MOH_IDLE_CFG_MOH_L2_PWR_SW(3);
		/* fall through */
	case POWER_MODE_CORE_INTIDLE:
		break;
	}

	/* program the memory controller hardware sleep type and auto wakeup */
	idle_cfg |= APMU_MOH_IDLE_CFG_MOH_DIS_MC_SW_REQ;
	idle_cfg |= APMU_MOH_IDLE_CFG_MOH_MC_WAKE_EN;
	__raw_writel(0x0, APMU_MC_HW_SLP_TYPE);		/* auto refresh */

	/* set DSPSD, DTCMSD, BBSD, MSASLPEN */
	apcr |= MPMU_APCR_DSPSD | MPMU_APCR_DTCMSD | MPMU_APCR_BBSD
		| MPMU_APCR_MSASLPEN;

	/*always set SLEPEN bit mainly for MSA*/
	apcr |= MPMU_APCR_SLPEN;

	/* finally write the registers back */
	__raw_writel(idle_cfg, APMU_MOH_IDLE_CFG);
	__raw_writel(apcr, MPMU_APCR);

}