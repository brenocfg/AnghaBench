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
struct tty_struct {int /*<<< orphan*/  name; struct isi_port* driver_data; } ;
struct TYPE_2__ {unsigned char* xmit_buf; } ;
struct isi_port {int xmit_cnt; int xmit_head; TYPE_1__ port; struct isi_board* card; } ;
struct isi_board {int /*<<< orphan*/  card_lock; } ;

/* Variables and functions */
 int SERIAL_XMIT_SIZE ; 
 scalar_t__ isicom_paranoia_check (struct isi_port*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int isicom_put_char(struct tty_struct *tty, unsigned char ch)
{
	struct isi_port *port = tty->driver_data;
	struct isi_board *card = port->card;
	unsigned long flags;

	if (isicom_paranoia_check(port, tty->name, "isicom_put_char"))
		return 0;

	spin_lock_irqsave(&card->card_lock, flags);
	if (port->xmit_cnt >= SERIAL_XMIT_SIZE - 1) {
		spin_unlock_irqrestore(&card->card_lock, flags);
		return 0;
	}

	port->port.xmit_buf[port->xmit_head++] = ch;
	port->xmit_head &= (SERIAL_XMIT_SIZE - 1);
	port->xmit_cnt++;
	spin_unlock_irqrestore(&card->card_lock, flags);
	return 1;
}