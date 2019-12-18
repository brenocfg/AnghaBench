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
typedef  int u32 ;
struct ibm_struct {TYPE_3__* acpi; } ;
struct TYPE_8__ {int /*<<< orphan*/  hotkey_wlsw; } ;
struct TYPE_7__ {TYPE_2__* device; } ;
struct TYPE_5__ {int /*<<< orphan*/  device_class; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; TYPE_1__ pnp; } ;

/* Variables and functions */
 int TPACPI_MAIL ; 
#define  TP_HKEY_EV_BAYEJ_ACK 129 
#define  TP_HKEY_EV_OPTDRV_EJ 128 
 int TP_HKEY_EV_RFKILL_CHANGED ; 
 int /*<<< orphan*/  acpi_bus_generate_netlink_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int*,char*,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hkey_handle ; 
 int hotkey_autosleep_ack ; 
 int hotkey_notify_6xxx (int,int*,int*) ; 
 int hotkey_notify_dockevent (int,int*,int*) ; 
 int hotkey_notify_hotkey (int,int*,int*) ; 
 int hotkey_notify_usrevent (int,int*,int*) ; 
 int hotkey_notify_wakeup (int,int*,int*) ; 
 int /*<<< orphan*/  hotkey_wakeup_hotunplug_complete_notify_change () ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_notice (char*,int) ; 
 TYPE_4__ tp_features ; 
 int /*<<< orphan*/  tpacpi_send_radiosw_update () ; 

__attribute__((used)) static void hotkey_notify(struct ibm_struct *ibm, u32 event)
{
	u32 hkey;
	bool send_acpi_ev;
	bool ignore_acpi_ev;
	bool known_ev;

	if (event != 0x80) {
		pr_err("unknown HKEY notification event %d\n", event);
		/* forward it to userspace, maybe it knows how to handle it */
		acpi_bus_generate_netlink_event(
					ibm->acpi->device->pnp.device_class,
					dev_name(&ibm->acpi->device->dev),
					event, 0);
		return;
	}

	while (1) {
		if (!acpi_evalf(hkey_handle, &hkey, "MHKP", "d")) {
			pr_err("failed to retrieve HKEY event\n");
			return;
		}

		if (hkey == 0) {
			/* queue empty */
			return;
		}

		send_acpi_ev = true;
		ignore_acpi_ev = false;

		switch (hkey >> 12) {
		case 1:
			/* 0x1000-0x1FFF: key presses */
			known_ev = hotkey_notify_hotkey(hkey, &send_acpi_ev,
						 &ignore_acpi_ev);
			break;
		case 2:
			/* 0x2000-0x2FFF: Wakeup reason */
			known_ev = hotkey_notify_wakeup(hkey, &send_acpi_ev,
						 &ignore_acpi_ev);
			break;
		case 3:
			/* 0x3000-0x3FFF: bay-related wakeups */
			switch (hkey) {
			case TP_HKEY_EV_BAYEJ_ACK:
				hotkey_autosleep_ack = 1;
				pr_info("bay ejected\n");
				hotkey_wakeup_hotunplug_complete_notify_change();
				known_ev = true;
				break;
			case TP_HKEY_EV_OPTDRV_EJ:
				/* FIXME: kick libata if SATA link offline */
				known_ev = true;
				break;
			default:
				known_ev = false;
			}
			break;
		case 4:
			/* 0x4000-0x4FFF: dock-related events */
			known_ev = hotkey_notify_dockevent(hkey, &send_acpi_ev,
						&ignore_acpi_ev);
			break;
		case 5:
			/* 0x5000-0x5FFF: human interface helpers */
			known_ev = hotkey_notify_usrevent(hkey, &send_acpi_ev,
						 &ignore_acpi_ev);
			break;
		case 6:
			/* 0x6000-0x6FFF: thermal alarms/notices and
			 *                keyboard events */
			known_ev = hotkey_notify_6xxx(hkey, &send_acpi_ev,
						 &ignore_acpi_ev);
			break;
		case 7:
			/* 0x7000-0x7FFF: misc */
			if (tp_features.hotkey_wlsw &&
					hkey == TP_HKEY_EV_RFKILL_CHANGED) {
				tpacpi_send_radiosw_update();
				send_acpi_ev = 0;
				known_ev = true;
				break;
			}
			/* fallthrough - to default */
		default:
			known_ev = false;
		}
		if (!known_ev) {
			pr_notice("unhandled HKEY event 0x%04x\n", hkey);
			pr_notice("please report the conditions when this event happened to %s\n",
				  TPACPI_MAIL);
		}

		/* netlink events */
		if (!ignore_acpi_ev && send_acpi_ev) {
			acpi_bus_generate_netlink_event(
					ibm->acpi->device->pnp.device_class,
					dev_name(&ibm->acpi->device->dev),
					event, hkey);
		}
	}
}