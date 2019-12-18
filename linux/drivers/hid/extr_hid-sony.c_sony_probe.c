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
struct sony_sc {unsigned long quirks; struct hid_device* hdev; int /*<<< orphan*/  lock; } ;
struct hid_device_id {unsigned long driver_data; } ;
struct hid_device {int version; int claimed; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DUALSHOCK4_CONTROLLER ; 
 int ENODEV ; 
 int ENOMEM ; 
 unsigned long FUTUREMAX_DANCE_MAT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HID_CLAIMED_INPUT ; 
 unsigned int HID_CONNECT_DEFAULT ; 
 unsigned int HID_CONNECT_HIDDEV_FORCE ; 
 unsigned long SHANWAN_GAMEPAD ; 
 int SIXAXIS_CONTROLLER ; 
 int VAIO_RDESC_CONSTANT ; 
 struct sony_sc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int hid_hw_start (struct hid_device*,unsigned int) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct sony_sc*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sony_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	int ret;
	unsigned long quirks = id->driver_data;
	struct sony_sc *sc;
	unsigned int connect_mask = HID_CONNECT_DEFAULT;

	if (!strcmp(hdev->name, "FutureMax Dance Mat"))
		quirks |= FUTUREMAX_DANCE_MAT;

	if (!strcmp(hdev->name, "SHANWAN PS3 GamePad"))
		quirks |= SHANWAN_GAMEPAD;

	sc = devm_kzalloc(&hdev->dev, sizeof(*sc), GFP_KERNEL);
	if (sc == NULL) {
		hid_err(hdev, "can't alloc sony descriptor\n");
		return -ENOMEM;
	}

	spin_lock_init(&sc->lock);

	sc->quirks = quirks;
	hid_set_drvdata(hdev, sc);
	sc->hdev = hdev;

	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "parse failed\n");
		return ret;
	}

	if (sc->quirks & VAIO_RDESC_CONSTANT)
		connect_mask |= HID_CONNECT_HIDDEV_FORCE;
	else if (sc->quirks & SIXAXIS_CONTROLLER)
		connect_mask |= HID_CONNECT_HIDDEV_FORCE;

	/* Patch the hw version on DS3/4 compatible devices, so applications can
	 * distinguish between the default HID mappings and the mappings defined
	 * by the Linux game controller spec. This is important for the SDL2
	 * library, which has a game controller database, which uses device ids
	 * in combination with version as a key.
	 */
	if (sc->quirks & (SIXAXIS_CONTROLLER | DUALSHOCK4_CONTROLLER))
		hdev->version |= 0x8000;

	ret = hid_hw_start(hdev, connect_mask);
	if (ret) {
		hid_err(hdev, "hw start failed\n");
		return ret;
	}

	/* sony_input_configured can fail, but this doesn't result
	 * in hid_hw_start failures (intended). Check whether
	 * the HID layer claimed the device else fail.
	 * We don't know the actual reason for the failure, most
	 * likely it is due to EEXIST in case of double connection
	 * of USB and Bluetooth, but could have been due to ENOMEM
	 * or other reasons as well.
	 */
	if (!(hdev->claimed & HID_CLAIMED_INPUT)) {
		hid_err(hdev, "failed to claim input\n");
		hid_hw_stop(hdev);
		return -ENODEV;
	}

	return ret;
}