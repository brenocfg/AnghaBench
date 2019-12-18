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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int charger_connected; } ;
struct pm2xxx_charger {int ac_conn; int /*<<< orphan*/  ac_work; int /*<<< orphan*/  charger_wq; TYPE_1__ ac; } ;

/* Variables and functions */
 int pm2xxx_charger_detection (struct pm2xxx_charger*,scalar_t__*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pm2xxx_charger_itv_pwr_plug_mngt(struct pm2xxx_charger *pm2, int val)
{

	int ret;
	u8 read_val;

	/*
	 * Since we can't be sure that the events are received
	 * synchronously, we have the check if the main charger is
	 * connected by reading the interrupt source register.
	 */
	ret = pm2xxx_charger_detection(pm2, &read_val);

	if ((ret == 0) && read_val) {
		pm2->ac.charger_connected = 1;
		pm2->ac_conn = true;
		queue_work(pm2->charger_wq, &pm2->ac_work);
	}


	return ret;
}