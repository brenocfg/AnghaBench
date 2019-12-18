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
typedef  int u8 ;
struct tps65010 {int nmask2; int regstatus; int nmask1; int chgstatus; int chgconf; unsigned int charging; scalar_t__ model; int /*<<< orphan*/  work; int /*<<< orphan*/  flags; int /*<<< orphan*/  por; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  FLAG_VBUS_CHANGED ; 
 int /*<<< orphan*/  POWER_POLL_DELAY ; 
 scalar_t__ TPS65013 ; 
 int TPS_CHARGE_ENABLE ; 
 int /*<<< orphan*/  TPS_CHGSTATUS ; 
 int TPS_CHG_AC ; 
 int TPS_CHG_USB ; 
 int /*<<< orphan*/  TPS_REGSTATUS ; 
 int TPS_REG_ONOFF ; 
 int /*<<< orphan*/  hibernate () ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_chgconfig (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  show_chgstatus (char*,int) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static void tps65010_interrupt(struct tps65010 *tps)
{
	u8 tmp = 0, mask, poll;

	/* IRQs won't trigger for certain events, but we can get
	 * others by polling (normally, with external power applied).
	 */
	poll = 0;

	/* regstatus irqs */
	if (tps->nmask2) {
		tmp = i2c_smbus_read_byte_data(tps->client, TPS_REGSTATUS);
		mask = tmp ^ tps->regstatus;
		tps->regstatus = tmp;
		mask &= tps->nmask2;
	} else
		mask = 0;
	if (mask) {
		tps->regstatus =  tmp;
		/* may need to shut something down ... */

		/* "off" usually means deep sleep */
		if (tmp & TPS_REG_ONOFF) {
			pr_info("%s: power off button\n", DRIVER_NAME);
#if 0
			/* REVISIT:  this might need its own workqueue
			 * plus tweaks including deadlock avoidance ...
			 * also needs to get error handling and probably
			 * an #ifdef CONFIG_HIBERNATION
			 */
			hibernate();
#endif
			poll = 1;
		}
	}

	/* chgstatus irqs */
	if (tps->nmask1) {
		tmp = i2c_smbus_read_byte_data(tps->client, TPS_CHGSTATUS);
		mask = tmp ^ tps->chgstatus;
		tps->chgstatus = tmp;
		mask &= tps->nmask1;
	} else
		mask = 0;
	if (mask) {
		unsigned	charging = 0;

		show_chgstatus("chg/irq", tmp);
		if (tmp & (TPS_CHG_USB|TPS_CHG_AC))
			show_chgconfig(tps->por, "conf", tps->chgconf);

		/* Unless it was turned off or disabled, we charge any
		 * battery whenever there's power available for it
		 * and the charger hasn't been disabled.
		 */
		if (!(tps->chgstatus & ~(TPS_CHG_USB|TPS_CHG_AC))
				&& (tps->chgstatus & (TPS_CHG_USB|TPS_CHG_AC))
				&& (tps->chgconf & TPS_CHARGE_ENABLE)
				) {
			if (tps->chgstatus & TPS_CHG_USB) {
				/* VBUS options are readonly until reconnect */
				if (mask & TPS_CHG_USB)
					set_bit(FLAG_VBUS_CHANGED, &tps->flags);
				charging = 1;
			} else if (tps->chgstatus & TPS_CHG_AC)
				charging = 1;
		}
		if (charging != tps->charging) {
			tps->charging = charging;
			pr_info("%s: battery %scharging\n",
				DRIVER_NAME, charging ? "" :
				((tps->chgstatus & (TPS_CHG_USB|TPS_CHG_AC))
					? "NOT " : "dis"));
		}
	}

	/* always poll to detect (a) power removal, without tps65013
	 * NO_CHG IRQ; or (b) restart of charging after stop.
	 */
	if ((tps->model != TPS65013 || !tps->charging)
			&& (tps->chgstatus & (TPS_CHG_USB|TPS_CHG_AC)))
		poll = 1;
	if (poll)
		queue_delayed_work(system_power_efficient_wq, &tps->work,
				   POWER_POLL_DELAY);

	/* also potentially gpio-in rise or fall */
}