#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pmic_wrapper {int /*<<< orphan*/  dev; TYPE_2__* slave; TYPE_1__* master; } ;
struct TYPE_4__ {int type; int /*<<< orphan*/ * dew_regs; } ;
struct TYPE_3__ {int type; } ;

/* Variables and functions */
 int EFAULT ; 
#define  PMIC_MT6323 139 
#define  PMIC_MT6351 138 
#define  PMIC_MT6357 137 
#define  PMIC_MT6397 136 
 int /*<<< orphan*/  PWRAP_CIPHER_EN ; 
 int /*<<< orphan*/  PWRAP_CIPHER_IV_SEL ; 
 int /*<<< orphan*/  PWRAP_CIPHER_KEY_SEL ; 
 int /*<<< orphan*/  PWRAP_CIPHER_LOAD ; 
 int /*<<< orphan*/  PWRAP_CIPHER_MODE ; 
 int /*<<< orphan*/  PWRAP_CIPHER_START ; 
 int /*<<< orphan*/  PWRAP_CIPHER_SWRST ; 
 size_t PWRAP_DEW_CIPHER_EN ; 
 size_t PWRAP_DEW_CIPHER_IV_SEL ; 
 size_t PWRAP_DEW_CIPHER_KEY_SEL ; 
 size_t PWRAP_DEW_CIPHER_LOAD ; 
 size_t PWRAP_DEW_CIPHER_MODE ; 
 size_t PWRAP_DEW_CIPHER_START ; 
 size_t PWRAP_DEW_CIPHER_SWRST ; 
 size_t PWRAP_DEW_WRITE_TEST ; 
 int PWRAP_DEW_WRITE_TEST_VAL ; 
#define  PWRAP_MT2701 135 
#define  PWRAP_MT6765 134 
#define  PWRAP_MT6797 133 
#define  PWRAP_MT7622 132 
#define  PWRAP_MT8135 131 
#define  PWRAP_MT8173 130 
#define  PWRAP_MT8183 129 
#define  PWRAP_MT8516 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pwrap_is_cipher_ready ; 
 int /*<<< orphan*/  pwrap_is_fsm_idle_and_sync_idle ; 
 int /*<<< orphan*/  pwrap_is_pmic_cipher_ready ; 
 scalar_t__ pwrap_read (struct pmic_wrapper*,int /*<<< orphan*/ ,int*) ; 
 int pwrap_wait_for_state (struct pmic_wrapper*,int /*<<< orphan*/ ) ; 
 scalar_t__ pwrap_write (struct pmic_wrapper*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pwrap_writel (struct pmic_wrapper*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pwrap_init_cipher(struct pmic_wrapper *wrp)
{
	int ret;
	u32 rdata = 0;

	pwrap_writel(wrp, 0x1, PWRAP_CIPHER_SWRST);
	pwrap_writel(wrp, 0x0, PWRAP_CIPHER_SWRST);
	pwrap_writel(wrp, 0x1, PWRAP_CIPHER_KEY_SEL);
	pwrap_writel(wrp, 0x2, PWRAP_CIPHER_IV_SEL);

	switch (wrp->master->type) {
	case PWRAP_MT8135:
		pwrap_writel(wrp, 1, PWRAP_CIPHER_LOAD);
		pwrap_writel(wrp, 1, PWRAP_CIPHER_START);
		break;
	case PWRAP_MT2701:
	case PWRAP_MT6765:
	case PWRAP_MT6797:
	case PWRAP_MT8173:
	case PWRAP_MT8516:
		pwrap_writel(wrp, 1, PWRAP_CIPHER_EN);
		break;
	case PWRAP_MT7622:
		pwrap_writel(wrp, 0, PWRAP_CIPHER_EN);
		break;
	case PWRAP_MT8183:
		break;
	}

	/* Config cipher mode @PMIC */
	pwrap_write(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_SWRST], 0x1);
	pwrap_write(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_SWRST], 0x0);
	pwrap_write(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_KEY_SEL], 0x1);
	pwrap_write(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_IV_SEL], 0x2);

	switch (wrp->slave->type) {
	case PMIC_MT6397:
		pwrap_write(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_LOAD],
			    0x1);
		pwrap_write(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_START],
			    0x1);
		break;
	case PMIC_MT6323:
	case PMIC_MT6351:
	case PMIC_MT6357:
		pwrap_write(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_EN],
			    0x1);
		break;
	default:
		break;
	}

	/* wait for cipher data ready@AP */
	ret = pwrap_wait_for_state(wrp, pwrap_is_cipher_ready);
	if (ret) {
		dev_err(wrp->dev, "cipher data ready@AP fail, ret=%d\n", ret);
		return ret;
	}

	/* wait for cipher data ready@PMIC */
	ret = pwrap_wait_for_state(wrp, pwrap_is_pmic_cipher_ready);
	if (ret) {
		dev_err(wrp->dev,
			"timeout waiting for cipher data ready@PMIC\n");
		return ret;
	}

	/* wait for cipher mode idle */
	pwrap_write(wrp, wrp->slave->dew_regs[PWRAP_DEW_CIPHER_MODE], 0x1);
	ret = pwrap_wait_for_state(wrp, pwrap_is_fsm_idle_and_sync_idle);
	if (ret) {
		dev_err(wrp->dev, "cipher mode idle fail, ret=%d\n", ret);
		return ret;
	}

	pwrap_writel(wrp, 1, PWRAP_CIPHER_MODE);

	/* Write Test */
	if (pwrap_write(wrp, wrp->slave->dew_regs[PWRAP_DEW_WRITE_TEST],
			PWRAP_DEW_WRITE_TEST_VAL) ||
	    pwrap_read(wrp, wrp->slave->dew_regs[PWRAP_DEW_WRITE_TEST],
		       &rdata) ||
	    (rdata != PWRAP_DEW_WRITE_TEST_VAL)) {
		dev_err(wrp->dev, "rdata=0x%04X\n", rdata);
		return -EFAULT;
	}

	return 0;
}