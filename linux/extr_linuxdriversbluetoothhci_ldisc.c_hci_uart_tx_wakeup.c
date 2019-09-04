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
struct hci_uart {int /*<<< orphan*/  proto_lock; int /*<<< orphan*/  write_work; int /*<<< orphan*/  tx_state; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  HCI_UART_PROTO_READY ; 
 int /*<<< orphan*/  HCI_UART_SENDING ; 
 int /*<<< orphan*/  HCI_UART_TX_WAKEUP ; 
 int /*<<< orphan*/  percpu_down_read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hci_uart_tx_wakeup(struct hci_uart *hu)
{
	/* This may be called in an IRQ context, so we can't sleep. Therefore
	 * we try to acquire the lock only, and if that fails we assume the
	 * tty is being closed because that is the only time the write lock is
	 * acquired. If, however, at some point in the future the write lock
	 * is also acquired in other situations, then this must be revisited.
	 */
	if (!percpu_down_read_trylock(&hu->proto_lock))
		return 0;

	if (!test_bit(HCI_UART_PROTO_READY, &hu->flags))
		goto no_schedule;

	if (test_and_set_bit(HCI_UART_SENDING, &hu->tx_state)) {
		set_bit(HCI_UART_TX_WAKEUP, &hu->tx_state);
		goto no_schedule;
	}

	BT_DBG("");

	schedule_work(&hu->write_work);

no_schedule:
	percpu_up_read(&hu->proto_lock);

	return 0;
}