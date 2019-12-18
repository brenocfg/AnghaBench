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
struct tty_struct {struct gsm_dlci* driver_data; } ;
struct gsm_dlci {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  fifo; } ;

/* Variables and functions */
 scalar_t__ DLCI_CLOSED ; 
 int EINVAL ; 
 int /*<<< orphan*/  gsm_dlci_data_kick (struct gsm_dlci*) ; 
 int kfifo_in_locked (int /*<<< orphan*/ ,unsigned char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gsmtty_write(struct tty_struct *tty, const unsigned char *buf,
								    int len)
{
	int sent;
	struct gsm_dlci *dlci = tty->driver_data;
	if (dlci->state == DLCI_CLOSED)
		return -EINVAL;
	/* Stuff the bytes into the fifo queue */
	sent = kfifo_in_locked(dlci->fifo, buf, len, &dlci->lock);
	/* Need to kick the channel */
	gsm_dlci_data_kick(dlci);
	return sent;
}