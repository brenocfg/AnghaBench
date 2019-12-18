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
struct power_supply {int dummy; } ;
struct abx500_chargalg {int /*<<< orphan*/  chargalg_work; int /*<<< orphan*/  chargalg_wq; } ;

/* Variables and functions */
 struct abx500_chargalg* power_supply_get_drvdata (struct power_supply*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void abx500_chargalg_external_power_changed(struct power_supply *psy)
{
	struct abx500_chargalg *di = power_supply_get_drvdata(psy);

	/*
	 * Trigger execution of the algorithm instantly and read
	 * all power_supply properties there instead
	 */
	queue_work(di->chargalg_wq, &di->chargalg_work);
}