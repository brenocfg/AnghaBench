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
struct steam_device {int client_opened; int quirks; int /*<<< orphan*/  work_connect; int /*<<< orphan*/  client_hdev; } ;
struct hid_device {scalar_t__ group; } ;

/* Variables and functions */
 scalar_t__ HID_GROUP_STEAM ; 
 int STEAM_QUIRK_WIRELESS ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_destroy_device (int /*<<< orphan*/ ) ; 
 struct steam_device* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_close (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*) ; 
 int /*<<< orphan*/  steam_unregister (struct steam_device*) ; 

__attribute__((used)) static void steam_remove(struct hid_device *hdev)
{
	struct steam_device *steam = hid_get_drvdata(hdev);

	if (!steam || hdev->group == HID_GROUP_STEAM) {
		hid_hw_stop(hdev);
		return;
	}

	hid_destroy_device(steam->client_hdev);
	steam->client_opened = false;
	cancel_work_sync(&steam->work_connect);
	if (steam->quirks & STEAM_QUIRK_WIRELESS) {
		hid_info(hdev, "Steam wireless receiver disconnected");
	}
	hid_hw_close(hdev);
	hid_hw_stop(hdev);
	steam_unregister(steam);
}