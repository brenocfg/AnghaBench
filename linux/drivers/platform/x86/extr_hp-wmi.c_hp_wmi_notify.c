#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int length; scalar_t__ pointer; } ;
union acpi_object {scalar_t__ type; TYPE_1__ buffer; } ;
typedef  int u32 ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ acpi_status ;
struct TYPE_7__ {int /*<<< orphan*/  swbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 scalar_t__ AE_OK ; 
#define  HPWMI_BACKLIT_KB_BRIGHTNESS 142 
#define  HPWMI_BATTERY_CHARGE_PERIOD 141 
#define  HPWMI_BEZEL_BUTTON 140 
 int /*<<< orphan*/  HPWMI_BLUETOOTH ; 
#define  HPWMI_COOLSENSE_SYSTEM_HOT 139 
#define  HPWMI_COOLSENSE_SYSTEM_MOBILE 138 
#define  HPWMI_CPU_BATTERY_THROTTLE 137 
#define  HPWMI_DOCK_EVENT 136 
 int /*<<< orphan*/  HPWMI_DOCK_MASK ; 
 int /*<<< orphan*/  HPWMI_HOTKEY_QUERY ; 
#define  HPWMI_LID_SWITCH 135 
#define  HPWMI_LOCK_SWITCH 134 
#define  HPWMI_PARK_HDD 133 
#define  HPWMI_PEAKSHIFT_PERIOD 132 
#define  HPWMI_PROXIMITY_SENSOR 131 
#define  HPWMI_SCREEN_ROTATION 130 
#define  HPWMI_SMART_ADAPTER 129 
 int /*<<< orphan*/  HPWMI_TABLET_MASK ; 
 int /*<<< orphan*/  HPWMI_WIFI ; 
#define  HPWMI_WIRELESS 128 
 int /*<<< orphan*/  HPWMI_WWAN ; 
 int /*<<< orphan*/  SW_DOCK ; 
 int /*<<< orphan*/  SW_TABLET_MODE ; 
 int /*<<< orphan*/  bluetooth_rfkill ; 
 int /*<<< orphan*/  hp_wmi_get_hw_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp_wmi_get_sw_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp_wmi_hw_state (int /*<<< orphan*/ ) ; 
 TYPE_2__* hp_wmi_input_dev ; 
 int hp_wmi_read_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp_wmi_rfkill2_refresh () ; 
 int /*<<< orphan*/  input_report_switch (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  rfkill2_count ; 
 int /*<<< orphan*/  rfkill_set_states (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparse_keymap_report_event (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wifi_rfkill ; 
 scalar_t__ wmi_get_event_data (int,struct acpi_buffer*) ; 
 int /*<<< orphan*/  wwan_rfkill ; 

__attribute__((used)) static void hp_wmi_notify(u32 value, void *context)
{
	struct acpi_buffer response = { ACPI_ALLOCATE_BUFFER, NULL };
	u32 event_id, event_data;
	union acpi_object *obj;
	acpi_status status;
	u32 *location;
	int key_code;

	status = wmi_get_event_data(value, &response);
	if (status != AE_OK) {
		pr_info("bad event status 0x%x\n", status);
		return;
	}

	obj = (union acpi_object *)response.pointer;

	if (!obj)
		return;
	if (obj->type != ACPI_TYPE_BUFFER) {
		pr_info("Unknown response received %d\n", obj->type);
		kfree(obj);
		return;
	}

	/*
	 * Depending on ACPI version the concatenation of id and event data
	 * inside _WED function will result in a 8 or 16 byte buffer.
	 */
	location = (u32 *)obj->buffer.pointer;
	if (obj->buffer.length == 8) {
		event_id = *location;
		event_data = *(location + 1);
	} else if (obj->buffer.length == 16) {
		event_id = *location;
		event_data = *(location + 2);
	} else {
		pr_info("Unknown buffer length %d\n", obj->buffer.length);
		kfree(obj);
		return;
	}
	kfree(obj);

	switch (event_id) {
	case HPWMI_DOCK_EVENT:
		if (test_bit(SW_DOCK, hp_wmi_input_dev->swbit))
			input_report_switch(hp_wmi_input_dev, SW_DOCK,
					    hp_wmi_hw_state(HPWMI_DOCK_MASK));
		if (test_bit(SW_TABLET_MODE, hp_wmi_input_dev->swbit))
			input_report_switch(hp_wmi_input_dev, SW_TABLET_MODE,
					    hp_wmi_hw_state(HPWMI_TABLET_MASK));
		input_sync(hp_wmi_input_dev);
		break;
	case HPWMI_PARK_HDD:
		break;
	case HPWMI_SMART_ADAPTER:
		break;
	case HPWMI_BEZEL_BUTTON:
		key_code = hp_wmi_read_int(HPWMI_HOTKEY_QUERY);
		if (key_code < 0)
			break;

		if (!sparse_keymap_report_event(hp_wmi_input_dev,
						key_code, 1, true))
			pr_info("Unknown key code - 0x%x\n", key_code);
		break;
	case HPWMI_WIRELESS:
		if (rfkill2_count) {
			hp_wmi_rfkill2_refresh();
			break;
		}

		if (wifi_rfkill)
			rfkill_set_states(wifi_rfkill,
					  hp_wmi_get_sw_state(HPWMI_WIFI),
					  hp_wmi_get_hw_state(HPWMI_WIFI));
		if (bluetooth_rfkill)
			rfkill_set_states(bluetooth_rfkill,
					  hp_wmi_get_sw_state(HPWMI_BLUETOOTH),
					  hp_wmi_get_hw_state(HPWMI_BLUETOOTH));
		if (wwan_rfkill)
			rfkill_set_states(wwan_rfkill,
					  hp_wmi_get_sw_state(HPWMI_WWAN),
					  hp_wmi_get_hw_state(HPWMI_WWAN));
		break;
	case HPWMI_CPU_BATTERY_THROTTLE:
		pr_info("Unimplemented CPU throttle because of 3 Cell battery event detected\n");
		break;
	case HPWMI_LOCK_SWITCH:
		break;
	case HPWMI_LID_SWITCH:
		break;
	case HPWMI_SCREEN_ROTATION:
		break;
	case HPWMI_COOLSENSE_SYSTEM_MOBILE:
		break;
	case HPWMI_COOLSENSE_SYSTEM_HOT:
		break;
	case HPWMI_PROXIMITY_SENSOR:
		break;
	case HPWMI_BACKLIT_KB_BRIGHTNESS:
		break;
	case HPWMI_PEAKSHIFT_PERIOD:
		break;
	case HPWMI_BATTERY_CHARGE_PERIOD:
		break;
	default:
		pr_info("Unknown event_id - %d - 0x%x\n", event_id, event_data);
		break;
	}
}