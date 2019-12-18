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
union power_supply_propval {int intval; int /*<<< orphan*/  strval; } ;
struct power_supply {int dummy; } ;
struct port_data {int psy_online; int psy_status; int psy_current_max; int psy_voltage_max_design; int psy_voltage_now; int psy_usb_type; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  model_name; struct charger_data* charger; } ;
struct device {int dummy; } ;
struct cros_ec_device {int /*<<< orphan*/  mkbp_event_supported; } ;
struct charger_data {struct device* dev; struct cros_ec_device* ec_device; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EC_POWER_LIMIT_NONE ; 
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CURRENT_MAX 137 
#define  POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT 136 
#define  POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT 135 
#define  POWER_SUPPLY_PROP_MANUFACTURER 134 
#define  POWER_SUPPLY_PROP_MODEL_NAME 133 
#define  POWER_SUPPLY_PROP_ONLINE 132 
#define  POWER_SUPPLY_PROP_STATUS 131 
#define  POWER_SUPPLY_PROP_USB_TYPE 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int cros_usbpd_charger_get_port_status (struct port_data*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int input_current_limit ; 
 int input_voltage_limit ; 
 struct port_data* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int cros_usbpd_charger_get_prop(struct power_supply *psy,
				       enum power_supply_property psp,
				       union power_supply_propval *val)
{
	struct port_data *port = power_supply_get_drvdata(psy);
	struct charger_data *charger = port->charger;
	struct cros_ec_device *ec_device = charger->ec_device;
	struct device *dev = charger->dev;
	int ret;

	/* Only refresh ec_port_status for dynamic properties */
	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		/*
		 * If mkbp_event_supported, then we can be assured that
		 * the driver's state for the online property is consistent
		 * with the hardware. However, if we aren't event driven,
		 * the optimization before to skip an ec_port_status get
		 * and only returned cached values of the online property will
		 * cause a delay in detecting a cable attach until one of the
		 * other properties are read.
		 *
		 * Allow an ec_port_status refresh for online property check
		 * if we're not already online to check for plug events if
		 * not mkbp_event_supported.
		 */
		if (ec_device->mkbp_event_supported || port->psy_online)
			break;
		/* fall through */
	case POWER_SUPPLY_PROP_CURRENT_MAX:
	case POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = cros_usbpd_charger_get_port_status(port, true);
		if (ret < 0) {
			dev_err(dev, "Failed to get port status (err:0x%x)\n",
				ret);
			return -EINVAL;
		}
		break;
	default:
		break;
	}

	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = port->psy_online;
		break;
	case POWER_SUPPLY_PROP_STATUS:
		val->intval = port->psy_status;
		break;
	case POWER_SUPPLY_PROP_CURRENT_MAX:
		val->intval = port->psy_current_max * 1000;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->intval = port->psy_voltage_max_design * 1000;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->intval = port->psy_voltage_now * 1000;
		break;
	case POWER_SUPPLY_PROP_USB_TYPE:
		val->intval = port->psy_usb_type;
		break;
	case POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		if (input_current_limit == EC_POWER_LIMIT_NONE)
			val->intval = -1;
		else
			val->intval = input_current_limit * 1000;
		break;
	case POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT:
		if (input_voltage_limit == EC_POWER_LIMIT_NONE)
			val->intval = -1;
		else
			val->intval = input_voltage_limit * 1000;
		break;
	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = port->model_name;
		break;
	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = port->manufacturer;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}