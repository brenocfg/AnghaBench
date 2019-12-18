#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  rx; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_1__* state; TYPE_2__ icount; } ;
struct sifive_serial_port {TYPE_3__ port; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int SIFIVE_RX_FIFO_DEPTH ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 unsigned char __ssp_receive_char (struct sifive_serial_port*,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_insert_char (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __ssp_receive_chars(struct sifive_serial_port *ssp)
{
	unsigned char ch;
	char is_empty;
	int c;

	for (c = SIFIVE_RX_FIFO_DEPTH; c > 0; --c) {
		ch = __ssp_receive_char(ssp, &is_empty);
		if (is_empty)
			break;

		ssp->port.icount.rx++;
		uart_insert_char(&ssp->port, 0, 0, ch, TTY_NORMAL);
	}

	spin_unlock(&ssp->port.lock);
	tty_flip_buffer_push(&ssp->port.state->port);
	spin_lock(&ssp->port.lock);
}