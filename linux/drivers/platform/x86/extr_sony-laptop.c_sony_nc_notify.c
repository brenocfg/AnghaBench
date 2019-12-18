#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct acpi_device {int dummy; } ;
struct TYPE_6__ {unsigned int* cap; } ;
struct TYPE_4__ {int /*<<< orphan*/  device_class; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; TYPE_1__ pnp; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  GFX_SWITCH ; 
 int /*<<< orphan*/  HOTKEY ; 
 int /*<<< orphan*/  KILLSWITCH ; 
 int __sony_nc_gfx_switch_status_get () ; 
 int /*<<< orphan*/  acpi_bus_generate_netlink_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 TYPE_3__* handles ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  sony_call_snc_handle (unsigned int,int,unsigned int*) ; 
 int /*<<< orphan*/  sony_laptop_report_input_event (int) ; 
 TYPE_2__* sony_nc_acpi_device ; 
 int /*<<< orphan*/  sony_nc_acpi_handle ; 
 int sony_nc_hotkeys_decode (int,unsigned int) ; 
 int /*<<< orphan*/  sony_nc_int_call (int /*<<< orphan*/ ,char*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  sony_nc_rfkill_update () ; 

__attribute__((used)) static void sony_nc_notify(struct acpi_device *device, u32 event)
{
	u32 real_ev = event;
	u8 ev_type = 0;
	int ret;

	dprintk("sony_nc_notify, event: 0x%.2x\n", event);

	if (event >= 0x90) {
		unsigned int result = 0;
		unsigned int arg = 0;
		unsigned int handle = 0;
		unsigned int offset = event - 0x90;

		if (offset >= ARRAY_SIZE(handles->cap)) {
			pr_err("Event 0x%x outside of capabilities list\n",
					event);
			return;
		}
		handle = handles->cap[offset];

		/* list of handles known for generating events */
		switch (handle) {
		/* hotkey event */
		case 0x0100:
		case 0x0127:
			ev_type = HOTKEY;
			ret = sony_nc_hotkeys_decode(event, handle);

			if (ret > 0) {
				sony_laptop_report_input_event(ret);
				real_ev = ret;
			}

			break;

		/* wlan switch */
		case 0x0124:
		case 0x0135:
			/* events on this handle are reported when the
			 * switch changes position or for battery
			 * events. We'll notify both of them but only
			 * update the rfkill device status when the
			 * switch is moved.
			 */
			ev_type = KILLSWITCH;
			sony_call_snc_handle(handle, 0x0100, &result);
			real_ev = result & 0x03;

			/* hw switch event */
			if (real_ev == 1)
				sony_nc_rfkill_update();

			break;

		case 0x0128:
		case 0x0146:
			/* Hybrid GFX switching */
			sony_call_snc_handle(handle, 0x0000, &result);
			dprintk("GFX switch event received (reason: %s)\n",
					(result == 0x1) ? "switch change" :
					(result == 0x2) ? "output switch" :
					(result == 0x3) ? "output switch" :
					"");

			ev_type = GFX_SWITCH;
			real_ev = __sony_nc_gfx_switch_status_get();
			break;

		case 0x015B:
			/* Hybrid GFX switching SVS151290S */
			ev_type = GFX_SWITCH;
			real_ev = __sony_nc_gfx_switch_status_get();
			break;
		default:
			dprintk("Unknown event 0x%x for handle 0x%x\n",
					event, handle);
			break;
		}

		/* clear the event (and the event reason when present) */
		arg = 1 << offset;
		sony_nc_int_call(sony_nc_acpi_handle, "SN05", &arg, &result);

	} else {
		/* old style event */
		ev_type = HOTKEY;
		sony_laptop_report_input_event(real_ev);
	}
	acpi_bus_generate_netlink_event(sony_nc_acpi_device->pnp.device_class,
			dev_name(&sony_nc_acpi_device->dev), ev_type, real_ev);
}