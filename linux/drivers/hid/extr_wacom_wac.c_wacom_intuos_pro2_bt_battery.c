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
struct wacom_wac {unsigned char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WACOM_POWER_SUPPLY_STATUS_AUTO ; 
 int /*<<< orphan*/  wacom_notify_battery (struct wacom_wac*,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void wacom_intuos_pro2_bt_battery(struct wacom_wac *wacom)
{
	unsigned char *data = wacom->data;

	bool chg = data[284] & 0x80;
	int battery_status = data[284] & 0x7F;

	wacom_notify_battery(wacom, WACOM_POWER_SUPPLY_STATUS_AUTO,
			     battery_status, chg, 1, chg);
}