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
struct wacom_wac {TYPE_2__* pen_input; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int WACOM_PKGLEN_MAX ; 
 int /*<<< orphan*/  WACOM_POWER_SUPPLY_STATUS_AUTO ; 
 unsigned int* batcap_i4 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned char,unsigned char,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wacom_intuos_bt_process_data (struct wacom_wac*,unsigned char*) ; 
 int /*<<< orphan*/  wacom_notify_battery (struct wacom_wac*,int /*<<< orphan*/ ,unsigned int,unsigned int,int,unsigned int) ; 

__attribute__((used)) static int wacom_intuos_bt_irq(struct wacom_wac *wacom, size_t len)
{
	unsigned char data[WACOM_PKGLEN_MAX];
	int i = 1;
	unsigned power_raw, battery_capacity, bat_charging, ps_connected;

	memcpy(data, wacom->data, len);

	switch (data[0]) {
	case 0x04:
		wacom_intuos_bt_process_data(wacom, data + i);
		i += 10;
		/* fall through */
	case 0x03:
		wacom_intuos_bt_process_data(wacom, data + i);
		i += 10;
		wacom_intuos_bt_process_data(wacom, data + i);
		i += 10;
		power_raw = data[i];
		bat_charging = (power_raw & 0x08) ? 1 : 0;
		ps_connected = (power_raw & 0x10) ? 1 : 0;
		battery_capacity = batcap_i4[power_raw & 0x07];
		wacom_notify_battery(wacom, WACOM_POWER_SUPPLY_STATUS_AUTO,
				     battery_capacity, bat_charging,
				     battery_capacity || bat_charging,
				     ps_connected);
		break;
	default:
		dev_dbg(wacom->pen_input->dev.parent,
				"Unknown report: %d,%d size:%zu\n",
				data[0], data[1], len);
		return 0;
	}
	return 0;
}