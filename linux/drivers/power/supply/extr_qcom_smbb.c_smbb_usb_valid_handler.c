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
struct smbb_charger {int status; int /*<<< orphan*/  usb_psy; int /*<<< orphan*/  edev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCON_USB ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int STATUS_USBIN_VALID ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smbb_set_line_flag (struct smbb_charger*,int,int) ; 

__attribute__((used)) static irqreturn_t smbb_usb_valid_handler(int irq, void *_data)
{
	struct smbb_charger *chg = _data;

	smbb_set_line_flag(chg, irq, STATUS_USBIN_VALID);
	extcon_set_state_sync(chg->edev, EXTCON_USB,
				chg->status & STATUS_USBIN_VALID);
	power_supply_changed(chg->usb_psy);

	return IRQ_HANDLED;
}