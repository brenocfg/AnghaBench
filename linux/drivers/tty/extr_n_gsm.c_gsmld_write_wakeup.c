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
struct tty_struct {int /*<<< orphan*/  flags; struct gsm_mux* disc_data; } ;
struct gsm_mux {scalar_t__ tx_bytes; int /*<<< orphan*/  tx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 scalar_t__ TX_THRESH_LO ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gsm_data_kick (struct gsm_mux*) ; 
 int /*<<< orphan*/  gsm_dlci_data_sweep (struct gsm_mux*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gsmld_write_wakeup(struct tty_struct *tty)
{
	struct gsm_mux *gsm = tty->disc_data;
	unsigned long flags;

	/* Queue poll */
	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	spin_lock_irqsave(&gsm->tx_lock, flags);
	gsm_data_kick(gsm);
	if (gsm->tx_bytes < TX_THRESH_LO) {
		gsm_dlci_data_sweep(gsm);
	}
	spin_unlock_irqrestore(&gsm->tx_lock, flags);
}