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
struct tps65910_board {int /*<<< orphan*/  en_ck32k_xtal; } ;
struct tps65910 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCTRL_CK32K_CTRL_MASK ; 
 int /*<<< orphan*/  TPS65910_DEVCTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int tps65910_reg_clear_bits (struct tps65910*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65910_ck32k_init(struct tps65910 *tps65910,
					struct tps65910_board *pmic_pdata)
{
	int ret;

	if (!pmic_pdata->en_ck32k_xtal)
		return 0;

	ret = tps65910_reg_clear_bits(tps65910, TPS65910_DEVCTRL,
						DEVCTRL_CK32K_CTRL_MASK);
	if (ret < 0) {
		dev_err(tps65910->dev, "clear ck32k_ctrl failed: %d\n", ret);
		return ret;
	}

	return 0;
}