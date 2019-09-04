#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int receive_room; struct hci_uart* disc_data; TYPE_1__* ops; } ;
struct hci_uart {int alignment; int /*<<< orphan*/  proto_lock; int /*<<< orphan*/  write_work; int /*<<< orphan*/  init_ready; scalar_t__ padding; struct tty_struct* tty; } ;
struct TYPE_2__ {int /*<<< orphan*/ * write; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct tty_struct*) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int ENFILE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_uart_init_work ; 
 int /*<<< orphan*/  hci_uart_write_work ; 
 struct hci_uart* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 

__attribute__((used)) static int hci_uart_tty_open(struct tty_struct *tty)
{
	struct hci_uart *hu;

	BT_DBG("tty %p", tty);

	/* Error if the tty has no write op instead of leaving an exploitable
	 * hole
	 */
	if (tty->ops->write == NULL)
		return -EOPNOTSUPP;

	hu = kzalloc(sizeof(struct hci_uart), GFP_KERNEL);
	if (!hu) {
		BT_ERR("Can't allocate control structure");
		return -ENFILE;
	}

	tty->disc_data = hu;
	hu->tty = tty;
	tty->receive_room = 65536;

	/* disable alignment support by default */
	hu->alignment = 1;
	hu->padding = 0;

	INIT_WORK(&hu->init_ready, hci_uart_init_work);
	INIT_WORK(&hu->write_work, hci_uart_write_work);

	percpu_init_rwsem(&hu->proto_lock);

	/* Flush any pending characters in the driver */
	tty_driver_flush_buffer(tty);

	return 0;
}