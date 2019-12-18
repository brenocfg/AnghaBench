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
typedef  int uint8_t ;
struct da9030_charger {int is_on; int mA; int mV; int fault; int /*<<< orphan*/  master; int /*<<< orphan*/  chdet; int /*<<< orphan*/  adc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9030_CHARGE_CONTROL ; 
 int DA9030_CHRG_CHARGER_ENABLE ; 
 int /*<<< orphan*/  DA9030_FAULT_LOG ; 
 int /*<<< orphan*/  DA9030_STATUS_CHDET ; 
 int /*<<< orphan*/  da9030_read_adc (struct da9030_charger*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da903x_query_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da903x_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void da9030_charger_update_state(struct da9030_charger *charger)
{
	uint8_t val;

	da903x_read(charger->master, DA9030_CHARGE_CONTROL, &val);
	charger->is_on = (val & DA9030_CHRG_CHARGER_ENABLE) ? 1 : 0;
	charger->mA = ((val >> 3) & 0xf) * 100;
	charger->mV = (val & 0x7) * 50 + 4000;

	da9030_read_adc(charger, &charger->adc);
	da903x_read(charger->master, DA9030_FAULT_LOG, &charger->fault);
	charger->chdet = da903x_query_status(charger->master,
						     DA9030_STATUS_CHDET);
}