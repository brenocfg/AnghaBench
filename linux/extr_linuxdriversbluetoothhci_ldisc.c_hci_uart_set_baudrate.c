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
struct ktermios {int /*<<< orphan*/  c_ospeed; int /*<<< orphan*/  c_ispeed; int /*<<< orphan*/  c_cflag; } ;
struct tty_struct {struct ktermios termios; } ;
struct hci_uart {TYPE_1__* hdev; struct tty_struct* tty; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CBAUD ; 
 int /*<<< orphan*/  tty_set_termios (struct tty_struct*,struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,unsigned int,unsigned int) ; 

void hci_uart_set_baudrate(struct hci_uart *hu, unsigned int speed)
{
	struct tty_struct *tty = hu->tty;
	struct ktermios ktermios;

	ktermios = tty->termios;
	ktermios.c_cflag &= ~CBAUD;
	tty_termios_encode_baud_rate(&ktermios, speed, speed);

	/* tty_set_termios() return not checked as it is always 0 */
	tty_set_termios(tty, &ktermios);

	BT_DBG("%s: New tty speeds: %d/%d", hu->hdev->name,
	       tty->termios.c_ispeed, tty->termios.c_ospeed);
}