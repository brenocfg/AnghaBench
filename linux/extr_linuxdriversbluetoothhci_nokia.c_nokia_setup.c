#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nokia_bt_dev {int initialized; int tx_enabled; scalar_t__ man_id; int /*<<< orphan*/  wakeup_bt; TYPE_2__* serdev; } ;
struct hci_uart {TYPE_1__* hdev; struct nokia_bt_dev* priv; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  quirks; int /*<<< orphan*/  set_bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_QUIRK_INVALID_BDADDR ; 
 int /*<<< orphan*/  MAX_BAUD_RATE ; 
 scalar_t__ NOKIA_ID_BCM2048 ; 
 int /*<<< orphan*/  btbcm_set_bdaddr ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nokia_flow_control (TYPE_2__*,int) ; 
 int nokia_reset (struct hci_uart*) ; 
 int nokia_send_alive_packet (struct hci_uart*) ; 
 int nokia_send_negotiation (struct hci_uart*) ; 
 int nokia_setup_fw (struct hci_uart*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  serdev_device_set_baudrate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nokia_setup(struct hci_uart *hu)
{
	struct nokia_bt_dev *btdev = hu->priv;
	struct device *dev = &btdev->serdev->dev;
	int err;

	btdev->initialized = false;

	nokia_flow_control(btdev->serdev, false);

	pm_runtime_get_sync(dev);

	if (btdev->tx_enabled) {
		gpiod_set_value_cansleep(btdev->wakeup_bt, 0);
		pm_runtime_put(&btdev->serdev->dev);
		btdev->tx_enabled = false;
	}

	dev_dbg(dev, "protocol setup");

	/* 0. reset connection */
	err = nokia_reset(hu);
	if (err < 0) {
		dev_err(dev, "Reset failed: %d", err);
		goto out;
	}

	/* 1. negotiate speed etc */
	err = nokia_send_negotiation(hu);
	if (err < 0) {
		dev_err(dev, "Negotiation failed: %d", err);
		goto out;
	}

	/* 2. verify correct setup using alive packet */
	err = nokia_send_alive_packet(hu);
	if (err < 0) {
		dev_err(dev, "Alive check failed: %d", err);
		goto out;
	}

	/* 3. send firmware */
	err = nokia_setup_fw(hu);
	if (err < 0) {
		dev_err(dev, "Could not setup FW: %d", err);
		goto out;
	}

	nokia_flow_control(btdev->serdev, false);
	serdev_device_set_baudrate(btdev->serdev, MAX_BAUD_RATE);
	nokia_flow_control(btdev->serdev, true);

	if (btdev->man_id == NOKIA_ID_BCM2048) {
		hu->hdev->set_bdaddr = btbcm_set_bdaddr;
		set_bit(HCI_QUIRK_INVALID_BDADDR, &hu->hdev->quirks);
		dev_dbg(dev, "bcm2048 has invalid bluetooth address!");
	}

	dev_dbg(dev, "protocol setup done!");

	gpiod_set_value_cansleep(btdev->wakeup_bt, 0);
	pm_runtime_put(dev);
	btdev->tx_enabled = false;
	btdev->initialized = true;

	return 0;
out:
	pm_runtime_put(dev);

	return err;
}