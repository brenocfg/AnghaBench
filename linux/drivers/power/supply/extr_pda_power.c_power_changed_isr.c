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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  wait_for_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 void* PDA_PSY_TO_CHANGE ; 
 void* ac_status ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  charger_work ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 void* pda_psy_ac ; 
 void* pda_psy_usb ; 
 TYPE_1__* pdata ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* usb_status ; 

__attribute__((used)) static irqreturn_t power_changed_isr(int irq, void *power_supply)
{
	if (power_supply == pda_psy_ac)
		ac_status = PDA_PSY_TO_CHANGE;
	else if (power_supply == pda_psy_usb)
		usb_status = PDA_PSY_TO_CHANGE;
	else
		return IRQ_NONE;

	/*
	 * Wait a bit before reading ac/usb line status and setting charger,
	 * because ac/usb status readings may lag from irq.
	 */
	cancel_delayed_work(&charger_work);
	schedule_delayed_work(&charger_work,
			      msecs_to_jiffies(pdata->wait_for_status));

	return IRQ_HANDLED;
}