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
struct hci_uart {scalar_t__ serdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hci_uart_set_baudrate (struct hci_uart*,unsigned int) ; 
 int /*<<< orphan*/  serdev_device_set_baudrate (scalar_t__,unsigned int) ; 

__attribute__((used)) static inline void host_set_baudrate(struct hci_uart *hu, unsigned int speed)
{
	if (hu->serdev)
		serdev_device_set_baudrate(hu->serdev, speed);
	else
		hci_uart_set_baudrate(hu, speed);
}