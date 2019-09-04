#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {struct hci_uart* disc_data; } ;
struct hci_uart {int hdev_flags; int /*<<< orphan*/  flags; TYPE_2__* hdev; TYPE_1__* proto; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int id; } ;
struct TYPE_3__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int EBADF ; 
 int EBUSY ; 
 int EUNATCH ; 
#define  HCIUARTGETDEVICE 132 
#define  HCIUARTGETFLAGS 131 
#define  HCIUARTGETPROTO 130 
#define  HCIUARTSETFLAGS 129 
#define  HCIUARTSETPROTO 128 
 int /*<<< orphan*/  HCI_UART_PROTO_SET ; 
 int /*<<< orphan*/  HCI_UART_REGISTERED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hci_uart_set_flags (struct hci_uart*,unsigned long) ; 
 int hci_uart_set_proto (struct hci_uart*,unsigned long) ; 
 int n_tty_ioctl_helper (struct tty_struct*,struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hci_uart_tty_ioctl(struct tty_struct *tty, struct file *file,
			      unsigned int cmd, unsigned long arg)
{
	struct hci_uart *hu = tty->disc_data;
	int err = 0;

	BT_DBG("");

	/* Verify the status of the device */
	if (!hu)
		return -EBADF;

	switch (cmd) {
	case HCIUARTSETPROTO:
		if (!test_and_set_bit(HCI_UART_PROTO_SET, &hu->flags)) {
			err = hci_uart_set_proto(hu, arg);
			if (err)
				clear_bit(HCI_UART_PROTO_SET, &hu->flags);
		} else
			err = -EBUSY;
		break;

	case HCIUARTGETPROTO:
		if (test_bit(HCI_UART_PROTO_SET, &hu->flags))
			err = hu->proto->id;
		else
			err = -EUNATCH;
		break;

	case HCIUARTGETDEVICE:
		if (test_bit(HCI_UART_REGISTERED, &hu->flags))
			err = hu->hdev->id;
		else
			err = -EUNATCH;
		break;

	case HCIUARTSETFLAGS:
		if (test_bit(HCI_UART_PROTO_SET, &hu->flags))
			err = -EBUSY;
		else
			err = hci_uart_set_flags(hu, arg);
		break;

	case HCIUARTGETFLAGS:
		err = hu->hdev_flags;
		break;

	default:
		err = n_tty_ioctl_helper(tty, file, cmd, arg);
		break;
	}

	return err;
}