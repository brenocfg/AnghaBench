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
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_PS_CTRL_REG ; 
 int /*<<< orphan*/  APMG_PS_CTRL_VAL_RESET_REQ ; 
 int /*<<< orphan*/  APMG_RTC_INT_MSK_REG ; 
 int /*<<< orphan*/  APMG_RTC_INT_STT_REG ; 
 int il_apm_init (struct il_priv*) ; 
 int /*<<< orphan*/  il_clear_bits_prph (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_set_bits_prph (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_wr_prph (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
il3945_apm_init(struct il_priv *il)
{
	int ret = il_apm_init(il);

	/* Clear APMG (NIC's internal power management) interrupts */
	il_wr_prph(il, APMG_RTC_INT_MSK_REG, 0x0);
	il_wr_prph(il, APMG_RTC_INT_STT_REG, 0xFFFFFFFF);

	/* Reset radio chip */
	il_set_bits_prph(il, APMG_PS_CTRL_REG, APMG_PS_CTRL_VAL_RESET_REQ);
	udelay(5);
	il_clear_bits_prph(il, APMG_PS_CTRL_REG, APMG_PS_CTRL_VAL_RESET_REQ);

	return ret;
}