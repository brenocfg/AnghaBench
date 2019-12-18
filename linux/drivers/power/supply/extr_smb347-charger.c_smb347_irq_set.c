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
struct smb347_charger {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_FAULT_IRQ ; 
 int CFG_FAULT_IRQ_DCIN_UV ; 
 int /*<<< orphan*/  CFG_PIN ; 
 int CFG_PIN_EN_CHARGER_ERROR ; 
 int /*<<< orphan*/  CFG_STATUS_IRQ ; 
 int CFG_STATUS_IRQ_CHARGE_TIMEOUT ; 
 int CFG_STATUS_IRQ_TERMINATION_OR_TAPER ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int smb347_set_writable (struct smb347_charger*,int) ; 

__attribute__((used)) static int smb347_irq_set(struct smb347_charger *smb, bool enable)
{
	int ret;

	ret = smb347_set_writable(smb, true);
	if (ret < 0)
		return ret;

	/*
	 * Enable/disable interrupts for:
	 *	- under voltage
	 *	- termination current reached
	 *	- charger timeout
	 *	- charger error
	 */
	ret = regmap_update_bits(smb->regmap, CFG_FAULT_IRQ, 0xff,
				 enable ? CFG_FAULT_IRQ_DCIN_UV : 0);
	if (ret < 0)
		goto fail;

	ret = regmap_update_bits(smb->regmap, CFG_STATUS_IRQ, 0xff,
			enable ? (CFG_STATUS_IRQ_TERMINATION_OR_TAPER |
					CFG_STATUS_IRQ_CHARGE_TIMEOUT) : 0);
	if (ret < 0)
		goto fail;

	ret = regmap_update_bits(smb->regmap, CFG_PIN, CFG_PIN_EN_CHARGER_ERROR,
				 enable ? CFG_PIN_EN_CHARGER_ERROR : 0);
fail:
	smb347_set_writable(smb, false);
	return ret;
}