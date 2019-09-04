#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sony_sc {int quirks; TYPE_1__* hdev; int /*<<< orphan*/ * mac_address; } ;
struct TYPE_4__ {int /*<<< orphan*/  uniq; } ;

/* Variables and functions */
 int DS4_FEATURE_REPORT_0x81_SIZE ; 
 int DUALSHOCK4_CONTROLLER_BT ; 
 int DUALSHOCK4_CONTROLLER_USB ; 
 int DUALSHOCK4_DONGLE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_REQ_GET_REPORT ; 
 int MOTION_CONTROLLER_BT ; 
 int NAVIGATION_CONTROLLER_BT ; 
 int NAVIGATION_CONTROLLER_USB ; 
 int SIXAXIS_CONTROLLER_BT ; 
 int SIXAXIS_CONTROLLER_USB ; 
 int SIXAXIS_REPORT_0xF2_SIZE ; 
 int /*<<< orphan*/  hid_err (TYPE_1__*,char*) ; 
 int hid_hw_raw_request (TYPE_1__*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *) ; 
 int sony_check_add_dev_list (struct sony_sc*) ; 
 scalar_t__ sony_get_bt_devaddr (struct sony_sc*) ; 

__attribute__((used)) static int sony_check_add(struct sony_sc *sc)
{
	u8 *buf = NULL;
	int n, ret;

	if ((sc->quirks & DUALSHOCK4_CONTROLLER_BT) ||
	    (sc->quirks & MOTION_CONTROLLER_BT) ||
	    (sc->quirks & NAVIGATION_CONTROLLER_BT) ||
	    (sc->quirks & SIXAXIS_CONTROLLER_BT)) {
		/*
		 * sony_get_bt_devaddr() attempts to parse the Bluetooth MAC
		 * address from the uniq string where HIDP stores it.
		 * As uniq cannot be guaranteed to be a MAC address in all cases
		 * a failure of this function should not prevent the connection.
		 */
		if (sony_get_bt_devaddr(sc) < 0) {
			hid_warn(sc->hdev, "UNIQ does not contain a MAC address; duplicate check skipped\n");
			return 0;
		}
	} else if (sc->quirks & (DUALSHOCK4_CONTROLLER_USB | DUALSHOCK4_DONGLE)) {
		buf = kmalloc(DS4_FEATURE_REPORT_0x81_SIZE, GFP_KERNEL);
		if (!buf)
			return -ENOMEM;

		/*
		 * The MAC address of a DS4 controller connected via USB can be
		 * retrieved with feature report 0x81. The address begins at
		 * offset 1.
		 */
		ret = hid_hw_raw_request(sc->hdev, 0x81, buf,
				DS4_FEATURE_REPORT_0x81_SIZE, HID_FEATURE_REPORT,
				HID_REQ_GET_REPORT);

		if (ret != DS4_FEATURE_REPORT_0x81_SIZE) {
			hid_err(sc->hdev, "failed to retrieve feature report 0x81 with the DualShock 4 MAC address\n");
			ret = ret < 0 ? ret : -EINVAL;
			goto out_free;
		}

		memcpy(sc->mac_address, &buf[1], sizeof(sc->mac_address));

		snprintf(sc->hdev->uniq, sizeof(sc->hdev->uniq),
			 "%pMR", sc->mac_address);
	} else if ((sc->quirks & SIXAXIS_CONTROLLER_USB) ||
			(sc->quirks & NAVIGATION_CONTROLLER_USB)) {
		buf = kmalloc(SIXAXIS_REPORT_0xF2_SIZE, GFP_KERNEL);
		if (!buf)
			return -ENOMEM;

		/*
		 * The MAC address of a Sixaxis controller connected via USB can
		 * be retrieved with feature report 0xf2. The address begins at
		 * offset 4.
		 */
		ret = hid_hw_raw_request(sc->hdev, 0xf2, buf,
				SIXAXIS_REPORT_0xF2_SIZE, HID_FEATURE_REPORT,
				HID_REQ_GET_REPORT);

		if (ret != SIXAXIS_REPORT_0xF2_SIZE) {
			hid_err(sc->hdev, "failed to retrieve feature report 0xf2 with the Sixaxis MAC address\n");
			ret = ret < 0 ? ret : -EINVAL;
			goto out_free;
		}

		/*
		 * The Sixaxis device MAC in the report is big-endian and must
		 * be byte-swapped.
		 */
		for (n = 0; n < 6; n++)
			sc->mac_address[5-n] = buf[4+n];

		snprintf(sc->hdev->uniq, sizeof(sc->hdev->uniq),
			 "%pMR", sc->mac_address);
	} else {
		return 0;
	}

	ret = sony_check_add_dev_list(sc);

out_free:

	kfree(buf);

	return ret;
}