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
struct serdev_device {int dummy; } ;
struct hci_uart {struct serdev_device* serdev; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 unsigned char QCA_WCN3990_POWEROFF_PULSE ; 
 int /*<<< orphan*/  hci_uart_set_flow_control (struct hci_uart*,int) ; 
 int /*<<< orphan*/  host_set_baudrate (struct hci_uart*,int) ; 
 int /*<<< orphan*/  qca_power_setup (struct hci_uart*,int) ; 
 int /*<<< orphan*/  serdev_device_write_buf (struct serdev_device*,unsigned char*,int) ; 

__attribute__((used)) static void qca_power_shutdown(struct hci_uart *hu)
{
	struct serdev_device *serdev = hu->serdev;
	unsigned char cmd = QCA_WCN3990_POWEROFF_PULSE;

	host_set_baudrate(hu, 2400);
	hci_uart_set_flow_control(hu, true);
	serdev_device_write_buf(serdev, &cmd, sizeof(cmd));
	hci_uart_set_flow_control(hu, false);
	qca_power_setup(hu, false);
}