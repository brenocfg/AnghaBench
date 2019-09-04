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
struct hci_uart {struct hci_dev* hdev; int /*<<< orphan*/  serdev; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCA_INIT_SPEED ; 
 int /*<<< orphan*/  QCA_WCN3990_POWEROFF_PULSE ; 
 int /*<<< orphan*/  QCA_WCN3990_POWERON_PULSE ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*) ; 
 int /*<<< orphan*/  hci_uart_set_flow_control (struct hci_uart*,int) ; 
 int /*<<< orphan*/  host_set_baudrate (struct hci_uart*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int qca_send_power_pulse (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qca_set_speed (struct hci_uart*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serdev_device_close (int /*<<< orphan*/ ) ; 
 int serdev_device_open (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qca_wcn3990_init(struct hci_uart *hu)
{
	struct hci_dev *hdev = hu->hdev;
	int ret;

	/* Forcefully enable wcn3990 to enter in to boot mode. */
	host_set_baudrate(hu, 2400);
	ret = qca_send_power_pulse(hdev, QCA_WCN3990_POWEROFF_PULSE);
	if (ret)
		return ret;

	qca_set_speed(hu, QCA_INIT_SPEED);
	ret = qca_send_power_pulse(hdev, QCA_WCN3990_POWERON_PULSE);
	if (ret)
		return ret;

	/* Wait for 100 ms for SoC to boot */
	msleep(100);

	/* Now the device is in ready state to communicate with host.
	 * To sync host with device we need to reopen port.
	 * Without this, we will have RTS and CTS synchronization
	 * issues.
	 */
	serdev_device_close(hu->serdev);
	ret = serdev_device_open(hu->serdev);
	if (ret) {
		bt_dev_err(hu->hdev, "failed to open port");
		return ret;
	}

	hci_uart_set_flow_control(hu, false);

	return 0;
}