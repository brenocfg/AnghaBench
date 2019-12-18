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
struct steam_device {int quirks; int client_opened; int /*<<< orphan*/  mutex; int /*<<< orphan*/  list; int /*<<< orphan*/ * serial_no; int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int STEAM_QUIRK_WIRELESS ; 
 int /*<<< orphan*/  hid_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lizard_mode ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  steam_battery_register (struct steam_device*) ; 
 int /*<<< orphan*/  steam_devices ; 
 int /*<<< orphan*/  steam_devices_lock ; 
 scalar_t__ steam_get_serial (struct steam_device*) ; 
 int steam_input_register (struct steam_device*) ; 
 int /*<<< orphan*/  steam_set_lizard_mode (struct steam_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int steam_register(struct steam_device *steam)
{
	int ret;
	bool client_opened;

	/*
	 * This function can be called several times in a row with the
	 * wireless adaptor, without steam_unregister() between them, because
	 * another client send a get_connection_status command, for example.
	 * The battery and serial number are set just once per device.
	 */
	if (!steam->serial_no[0]) {
		/*
		 * Unlikely, but getting the serial could fail, and it is not so
		 * important, so make up a serial number and go on.
		 */
		mutex_lock(&steam->mutex);
		if (steam_get_serial(steam) < 0)
			strlcpy(steam->serial_no, "XXXXXXXXXX",
					sizeof(steam->serial_no));
		mutex_unlock(&steam->mutex);

		hid_info(steam->hdev, "Steam Controller '%s' connected",
				steam->serial_no);

		/* ignore battery errors, we can live without it */
		if (steam->quirks & STEAM_QUIRK_WIRELESS)
			steam_battery_register(steam);

		mutex_lock(&steam_devices_lock);
		list_add(&steam->list, &steam_devices);
		mutex_unlock(&steam_devices_lock);
	}

	mutex_lock(&steam->mutex);
	client_opened = steam->client_opened;
	if (!client_opened)
		steam_set_lizard_mode(steam, lizard_mode);
	mutex_unlock(&steam->mutex);

	if (!client_opened)
		ret = steam_input_register(steam);
	else
		ret = 0;

	return ret;
}