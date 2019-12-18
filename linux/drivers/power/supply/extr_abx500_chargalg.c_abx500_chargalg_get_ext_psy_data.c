#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union power_supply_propval {int intval; } ;
struct power_supply {TYPE_2__* desc; int /*<<< orphan*/  num_supplicants; scalar_t__ supplied_to; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int percent; int volt; int temp; int inst_curr; int avg_curr; } ;
struct TYPE_7__ {int batt_rem; int mainextchnotok; int main_thermal_prot; int main_ovv; int ac_wd_expired; int usbchargernotok; int usb_thermal_prot; int vbus_ovv; int usb_wd_expired; int ac_cv_active; int usb_cv_active; int batt_unknown; int vbus_collapsed; } ;
struct TYPE_5__ {int conn_chg; int prev_conn_chg; int online_chg; int prev_online_chg; int ac_volt; int usb_volt; int ac_curr; int usb_curr; } ;
struct abx500_chargalg {TYPE_4__ batt_data; TYPE_3__ events; TYPE_1__ chg_info; int /*<<< orphan*/  chargalg_wd_work; int /*<<< orphan*/  chargalg_wq; void* usb_chg; void* ac_chg; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_6__ {int num_properties; int* properties; scalar_t__ type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int AC_CHG ; 
#define  POWER_SUPPLY_HEALTH_COLD 146 
#define  POWER_SUPPLY_HEALTH_DEAD 145 
#define  POWER_SUPPLY_HEALTH_GOOD 144 
#define  POWER_SUPPLY_HEALTH_OVERHEAT 143 
#define  POWER_SUPPLY_HEALTH_OVERVOLTAGE 142 
#define  POWER_SUPPLY_HEALTH_UNSPEC_FAILURE 141 
#define  POWER_SUPPLY_PROP_CAPACITY 140 
#define  POWER_SUPPLY_PROP_CURRENT_AVG 139 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 138 
#define  POWER_SUPPLY_PROP_HEALTH 137 
#define  POWER_SUPPLY_PROP_ONLINE 136 
#define  POWER_SUPPLY_PROP_PRESENT 135 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 134 
#define  POWER_SUPPLY_PROP_TEMP 133 
#define  POWER_SUPPLY_PROP_VOLTAGE_AVG 132 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 131 
#define  POWER_SUPPLY_TYPE_BATTERY 130 
#define  POWER_SUPPLY_TYPE_MAINS 129 
#define  POWER_SUPPLY_TYPE_USB 128 
 int USB_CHG ; 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 int match_string (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct abx500_chargalg* power_supply_get_drvdata (struct power_supply*) ; 
 scalar_t__ power_supply_get_property (struct power_supply*,int,union power_supply_propval*) ; 
 void* psy_to_ux500_charger (struct power_supply*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int abx500_chargalg_get_ext_psy_data(struct device *dev, void *data)
{
	struct power_supply *psy;
	struct power_supply *ext = dev_get_drvdata(dev);
	const char **supplicants = (const char **)ext->supplied_to;
	struct abx500_chargalg *di;
	union power_supply_propval ret;
	int j;
	bool capacity_updated = false;

	psy = (struct power_supply *)data;
	di = power_supply_get_drvdata(psy);
	/* For all psy where the driver name appears in any supplied_to */
	j = match_string(supplicants, ext->num_supplicants, psy->desc->name);
	if (j < 0)
		return 0;

	/*
	 *  If external is not registering 'POWER_SUPPLY_PROP_CAPACITY' to its
	 * property because of handling that sysfs entry on its own, this is
	 * the place to get the battery capacity.
	 */
	if (!power_supply_get_property(ext, POWER_SUPPLY_PROP_CAPACITY, &ret)) {
		di->batt_data.percent = ret.intval;
		capacity_updated = true;
	}

	/* Go through all properties for the psy */
	for (j = 0; j < ext->desc->num_properties; j++) {
		enum power_supply_property prop;
		prop = ext->desc->properties[j];

		/*
		 * Initialize chargers if not already done.
		 * The ab8500_charger*/
		if (!di->ac_chg &&
			ext->desc->type == POWER_SUPPLY_TYPE_MAINS)
			di->ac_chg = psy_to_ux500_charger(ext);
		else if (!di->usb_chg &&
			ext->desc->type == POWER_SUPPLY_TYPE_USB)
			di->usb_chg = psy_to_ux500_charger(ext);

		if (power_supply_get_property(ext, prop, &ret))
			continue;
		switch (prop) {
		case POWER_SUPPLY_PROP_PRESENT:
			switch (ext->desc->type) {
			case POWER_SUPPLY_TYPE_BATTERY:
				/* Battery present */
				if (ret.intval)
					di->events.batt_rem = false;
				/* Battery removed */
				else
					di->events.batt_rem = true;
				break;
			case POWER_SUPPLY_TYPE_MAINS:
				/* AC disconnected */
				if (!ret.intval &&
					(di->chg_info.conn_chg & AC_CHG)) {
					di->chg_info.prev_conn_chg =
						di->chg_info.conn_chg;
					di->chg_info.conn_chg &= ~AC_CHG;
				}
				/* AC connected */
				else if (ret.intval &&
					!(di->chg_info.conn_chg & AC_CHG)) {
					di->chg_info.prev_conn_chg =
						di->chg_info.conn_chg;
					di->chg_info.conn_chg |= AC_CHG;
				}
				break;
			case POWER_SUPPLY_TYPE_USB:
				/* USB disconnected */
				if (!ret.intval &&
					(di->chg_info.conn_chg & USB_CHG)) {
					di->chg_info.prev_conn_chg =
						di->chg_info.conn_chg;
					di->chg_info.conn_chg &= ~USB_CHG;
				}
				/* USB connected */
				else if (ret.intval &&
					!(di->chg_info.conn_chg & USB_CHG)) {
					di->chg_info.prev_conn_chg =
						di->chg_info.conn_chg;
					di->chg_info.conn_chg |= USB_CHG;
				}
				break;
			default:
				break;
			}
			break;

		case POWER_SUPPLY_PROP_ONLINE:
			switch (ext->desc->type) {
			case POWER_SUPPLY_TYPE_BATTERY:
				break;
			case POWER_SUPPLY_TYPE_MAINS:
				/* AC offline */
				if (!ret.intval &&
					(di->chg_info.online_chg & AC_CHG)) {
					di->chg_info.prev_online_chg =
						di->chg_info.online_chg;
					di->chg_info.online_chg &= ~AC_CHG;
				}
				/* AC online */
				else if (ret.intval &&
					!(di->chg_info.online_chg & AC_CHG)) {
					di->chg_info.prev_online_chg =
						di->chg_info.online_chg;
					di->chg_info.online_chg |= AC_CHG;
					queue_delayed_work(di->chargalg_wq,
						&di->chargalg_wd_work, 0);
				}
				break;
			case POWER_SUPPLY_TYPE_USB:
				/* USB offline */
				if (!ret.intval &&
					(di->chg_info.online_chg & USB_CHG)) {
					di->chg_info.prev_online_chg =
						di->chg_info.online_chg;
					di->chg_info.online_chg &= ~USB_CHG;
				}
				/* USB online */
				else if (ret.intval &&
					!(di->chg_info.online_chg & USB_CHG)) {
					di->chg_info.prev_online_chg =
						di->chg_info.online_chg;
					di->chg_info.online_chg |= USB_CHG;
					queue_delayed_work(di->chargalg_wq,
						&di->chargalg_wd_work, 0);
				}
				break;
			default:
				break;
			}
			break;

		case POWER_SUPPLY_PROP_HEALTH:
			switch (ext->desc->type) {
			case POWER_SUPPLY_TYPE_BATTERY:
				break;
			case POWER_SUPPLY_TYPE_MAINS:
				switch (ret.intval) {
				case POWER_SUPPLY_HEALTH_UNSPEC_FAILURE:
					di->events.mainextchnotok = true;
					di->events.main_thermal_prot = false;
					di->events.main_ovv = false;
					di->events.ac_wd_expired = false;
					break;
				case POWER_SUPPLY_HEALTH_DEAD:
					di->events.ac_wd_expired = true;
					di->events.mainextchnotok = false;
					di->events.main_ovv = false;
					di->events.main_thermal_prot = false;
					break;
				case POWER_SUPPLY_HEALTH_COLD:
				case POWER_SUPPLY_HEALTH_OVERHEAT:
					di->events.main_thermal_prot = true;
					di->events.mainextchnotok = false;
					di->events.main_ovv = false;
					di->events.ac_wd_expired = false;
					break;
				case POWER_SUPPLY_HEALTH_OVERVOLTAGE:
					di->events.main_ovv = true;
					di->events.mainextchnotok = false;
					di->events.main_thermal_prot = false;
					di->events.ac_wd_expired = false;
					break;
				case POWER_SUPPLY_HEALTH_GOOD:
					di->events.main_thermal_prot = false;
					di->events.mainextchnotok = false;
					di->events.main_ovv = false;
					di->events.ac_wd_expired = false;
					break;
				default:
					break;
				}
				break;

			case POWER_SUPPLY_TYPE_USB:
				switch (ret.intval) {
				case POWER_SUPPLY_HEALTH_UNSPEC_FAILURE:
					di->events.usbchargernotok = true;
					di->events.usb_thermal_prot = false;
					di->events.vbus_ovv = false;
					di->events.usb_wd_expired = false;
					break;
				case POWER_SUPPLY_HEALTH_DEAD:
					di->events.usb_wd_expired = true;
					di->events.usbchargernotok = false;
					di->events.usb_thermal_prot = false;
					di->events.vbus_ovv = false;
					break;
				case POWER_SUPPLY_HEALTH_COLD:
				case POWER_SUPPLY_HEALTH_OVERHEAT:
					di->events.usb_thermal_prot = true;
					di->events.usbchargernotok = false;
					di->events.vbus_ovv = false;
					di->events.usb_wd_expired = false;
					break;
				case POWER_SUPPLY_HEALTH_OVERVOLTAGE:
					di->events.vbus_ovv = true;
					di->events.usbchargernotok = false;
					di->events.usb_thermal_prot = false;
					di->events.usb_wd_expired = false;
					break;
				case POWER_SUPPLY_HEALTH_GOOD:
					di->events.usbchargernotok = false;
					di->events.usb_thermal_prot = false;
					di->events.vbus_ovv = false;
					di->events.usb_wd_expired = false;
					break;
				default:
					break;
				}
			default:
				break;
			}
			break;

		case POWER_SUPPLY_PROP_VOLTAGE_NOW:
			switch (ext->desc->type) {
			case POWER_SUPPLY_TYPE_BATTERY:
				di->batt_data.volt = ret.intval / 1000;
				break;
			case POWER_SUPPLY_TYPE_MAINS:
				di->chg_info.ac_volt = ret.intval / 1000;
				break;
			case POWER_SUPPLY_TYPE_USB:
				di->chg_info.usb_volt = ret.intval / 1000;
				break;
			default:
				break;
			}
			break;

		case POWER_SUPPLY_PROP_VOLTAGE_AVG:
			switch (ext->desc->type) {
			case POWER_SUPPLY_TYPE_MAINS:
				/* AVG is used to indicate when we are
				 * in CV mode */
				if (ret.intval)
					di->events.ac_cv_active = true;
				else
					di->events.ac_cv_active = false;

				break;
			case POWER_SUPPLY_TYPE_USB:
				/* AVG is used to indicate when we are
				 * in CV mode */
				if (ret.intval)
					di->events.usb_cv_active = true;
				else
					di->events.usb_cv_active = false;

				break;
			default:
				break;
			}
			break;

		case POWER_SUPPLY_PROP_TECHNOLOGY:
			switch (ext->desc->type) {
			case POWER_SUPPLY_TYPE_BATTERY:
				if (ret.intval)
					di->events.batt_unknown = false;
				else
					di->events.batt_unknown = true;

				break;
			default:
				break;
			}
			break;

		case POWER_SUPPLY_PROP_TEMP:
			di->batt_data.temp = ret.intval / 10;
			break;

		case POWER_SUPPLY_PROP_CURRENT_NOW:
			switch (ext->desc->type) {
			case POWER_SUPPLY_TYPE_MAINS:
					di->chg_info.ac_curr =
						ret.intval / 1000;
					break;
			case POWER_SUPPLY_TYPE_USB:
					di->chg_info.usb_curr =
						ret.intval / 1000;
				break;
			case POWER_SUPPLY_TYPE_BATTERY:
				di->batt_data.inst_curr = ret.intval / 1000;
				break;
			default:
				break;
			}
			break;

		case POWER_SUPPLY_PROP_CURRENT_AVG:
			switch (ext->desc->type) {
			case POWER_SUPPLY_TYPE_BATTERY:
				di->batt_data.avg_curr = ret.intval / 1000;
				break;
			case POWER_SUPPLY_TYPE_USB:
				if (ret.intval)
					di->events.vbus_collapsed = true;
				else
					di->events.vbus_collapsed = false;
				break;
			default:
				break;
			}
			break;
		case POWER_SUPPLY_PROP_CAPACITY:
			if (!capacity_updated)
				di->batt_data.percent = ret.intval;
			break;
		default:
			break;
		}
	}
	return 0;
}