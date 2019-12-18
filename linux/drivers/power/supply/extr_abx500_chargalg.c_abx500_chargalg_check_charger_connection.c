#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int conn_chg; int prev_conn_chg; int charger_type; } ;
struct TYPE_3__ {int suspended_change; scalar_t__ usb_suspended; scalar_t__ ac_suspended; } ;
struct abx500_chargalg {TYPE_2__ chg_info; TYPE_1__ susp_status; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AC_CHG ; 
 void* NO_CHG ; 
 int /*<<< orphan*/  STATE_HANDHELD_INIT ; 
 int /*<<< orphan*/  STATE_NORMAL_INIT ; 
 int /*<<< orphan*/  STATE_SUSPENDED_INIT ; 
 int USB_CHG ; 
 int /*<<< orphan*/  abx500_chargalg_state_to (struct abx500_chargalg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int abx500_chargalg_check_charger_connection(struct abx500_chargalg *di)
{
	if (di->chg_info.conn_chg != di->chg_info.prev_conn_chg ||
		di->susp_status.suspended_change) {
		/*
		 * Charger state changed or suspension
		 * has changed since last update
		 */
		if ((di->chg_info.conn_chg & AC_CHG) &&
			!di->susp_status.ac_suspended) {
			dev_dbg(di->dev, "Charging source is AC\n");
			if (di->chg_info.charger_type != AC_CHG) {
				di->chg_info.charger_type = AC_CHG;
				abx500_chargalg_state_to(di, STATE_NORMAL_INIT);
			}
		} else if ((di->chg_info.conn_chg & USB_CHG) &&
			!di->susp_status.usb_suspended) {
			dev_dbg(di->dev, "Charging source is USB\n");
			di->chg_info.charger_type = USB_CHG;
			abx500_chargalg_state_to(di, STATE_NORMAL_INIT);
		} else if (di->chg_info.conn_chg &&
			(di->susp_status.ac_suspended ||
			di->susp_status.usb_suspended)) {
			dev_dbg(di->dev, "Charging is suspended\n");
			di->chg_info.charger_type = NO_CHG;
			abx500_chargalg_state_to(di, STATE_SUSPENDED_INIT);
		} else {
			dev_dbg(di->dev, "Charging source is OFF\n");
			di->chg_info.charger_type = NO_CHG;
			abx500_chargalg_state_to(di, STATE_HANDHELD_INIT);
		}
		di->chg_info.prev_conn_chg = di->chg_info.conn_chg;
		di->susp_status.suspended_change = false;
	}
	return di->chg_info.conn_chg;
}