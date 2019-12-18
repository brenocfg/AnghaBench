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
struct tty_struct {int index; } ;
struct nozomi {int /*<<< orphan*/  spin_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG1 (char*) ; 
 int MAX_PORT ; 
 int /*<<< orphan*/  enable_transmit_dl (int,struct nozomi*) ; 
 struct nozomi* get_dc_by_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  set_rts (struct tty_struct*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ntty_unthrottle(struct tty_struct *tty)
{
	struct nozomi *dc = get_dc_by_tty(tty);
	unsigned long flags;

	DBG1("UNTHROTTLE");
	spin_lock_irqsave(&dc->spin_mutex, flags);
	enable_transmit_dl(tty->index % MAX_PORT, dc);
	set_rts(tty, 1);

	spin_unlock_irqrestore(&dc->spin_mutex, flags);
}