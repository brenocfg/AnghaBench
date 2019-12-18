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
struct pm2xxx_charger {int /*<<< orphan*/  check_main_thermal_prot_work; int /*<<< orphan*/  charger_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pm2xxx_charger_die_therm_mngt(struct pm2xxx_charger *pm2, int val)
{
	queue_work(pm2->charger_wq, &pm2->check_main_thermal_prot_work);

	return 0;
}