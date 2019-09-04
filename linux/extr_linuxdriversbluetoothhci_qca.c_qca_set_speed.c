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
struct hci_uart {int /*<<< orphan*/  hdev; } ;
typedef  enum qca_speed_type { ____Placeholder_qca_speed_type } qca_speed_type ;

/* Variables and functions */
 int QCA_INIT_SPEED ; 
 int QCA_OPER_SPEED ; 
 int /*<<< orphan*/  bt_dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  host_set_baudrate (struct hci_uart*,unsigned int) ; 
 unsigned int qca_get_baudrate_value (unsigned int) ; 
 unsigned int qca_get_speed (struct hci_uart*,int) ; 
 int qca_set_baudrate (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int qca_set_speed(struct hci_uart *hu, enum qca_speed_type speed_type)
{
	unsigned int speed, qca_baudrate;
	int ret;

	if (speed_type == QCA_INIT_SPEED) {
		speed = qca_get_speed(hu, QCA_INIT_SPEED);
		if (speed)
			host_set_baudrate(hu, speed);
	} else {
		speed = qca_get_speed(hu, QCA_OPER_SPEED);
		if (!speed)
			return 0;

		qca_baudrate = qca_get_baudrate_value(speed);
		bt_dev_dbg(hu->hdev, "Set UART speed to %d", speed);
		ret = qca_set_baudrate(hu->hdev, qca_baudrate);
		if (ret)
			return ret;

		host_set_baudrate(hu, speed);
	}

	return 0;
}