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
struct TYPE_2__ {int type; int /*<<< orphan*/ * dew_regs; } ;

/* Variables and functions */
#define  PMIC_MT6323 129 
#define  PMIC_MT6397 128 
 size_t PWRAP_DEW_RDDMY_NO ; 
 int /*<<< orphan*/  PWRAP_RDDMY ; 
 int /*<<< orphan*/  pwrap_init_chip_select_ext (struct pmic_wrapper*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pwrap_write (struct pmic_wrapper*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pwrap_writel (struct pmic_wrapper*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pwrap_mt2701_init_reg_clock(struct pmic_wrapper *wrp)
{
	switch (wrp->slave->type) {
	case PMIC_MT6397:
		pwrap_writel(wrp, 0xc, PWRAP_RDDMY);
		pwrap_init_chip_select_ext(wrp, 4, 0, 2, 2);
		break;

	case PMIC_MT6323:
		pwrap_writel(wrp, 0x8, PWRAP_RDDMY);
		pwrap_write(wrp, wrp->slave->dew_regs[PWRAP_DEW_RDDMY_NO],
			    0x8);
		pwrap_init_chip_select_ext(wrp, 5, 0, 2, 2);
		break;
	default:
		break;
	}

	return 0;
}