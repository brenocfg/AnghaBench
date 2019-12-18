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
struct tty_struct {scalar_t__ hw_stopped; scalar_t__ stopped; int /*<<< orphan*/  name; struct isi_port* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  xmit_buf; } ;
struct isi_port {scalar_t__ xmit_cnt; int /*<<< orphan*/  status; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISI_TXOK ; 
 scalar_t__ isicom_paranoia_check (struct isi_port*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void isicom_flush_chars(struct tty_struct *tty)
{
	struct isi_port *port = tty->driver_data;

	if (isicom_paranoia_check(port, tty->name, "isicom_flush_chars"))
		return;

	if (port->xmit_cnt <= 0 || tty->stopped || tty->hw_stopped ||
			!port->port.xmit_buf)
		return;

	/* this tells the transmitter to consider this port for
	   data output to the card ... that's the best we can do. */
	port->status |= ISI_TXOK;
}