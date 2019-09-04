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
struct hci_uart_proto {int dummy; } ;
struct hci_uart {int /*<<< orphan*/  flags; struct hci_uart_proto const* proto; } ;

/* Variables and functions */
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  HCI_UART_PROTO_READY ; 
 struct hci_uart_proto* hci_uart_get_proto (int) ; 
 int hci_uart_register_dev (struct hci_uart*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hci_uart_set_proto(struct hci_uart *hu, int id)
{
	const struct hci_uart_proto *p;
	int err;

	p = hci_uart_get_proto(id);
	if (!p)
		return -EPROTONOSUPPORT;

	hu->proto = p;

	err = hci_uart_register_dev(hu);
	if (err) {
		return err;
	}

	set_bit(HCI_UART_PROTO_READY, &hu->flags);
	return 0;
}