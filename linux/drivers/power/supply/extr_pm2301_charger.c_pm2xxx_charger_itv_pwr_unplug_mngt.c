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
struct TYPE_2__ {scalar_t__ charger_connected; } ;
struct pm2xxx_charger {int /*<<< orphan*/  ac_work; int /*<<< orphan*/  charger_wq; TYPE_1__ ac; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pm2xxx_charger_itv_pwr_unplug_mngt(struct pm2xxx_charger *pm2,
								int val)
{
	pm2->ac.charger_connected = 0;
	queue_work(pm2->charger_wq, &pm2->ac_work);

	return 0;
}