#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int c_cflag; int /*<<< orphan*/  c_iflag; } ;
struct tty_struct {scalar_t__ hw_stopped; TYPE_2__ termios; TYPE_1__* driver; scalar_t__ driver_data; } ;
struct ktermios {int c_cflag; int /*<<< orphan*/  c_iflag; } ;
struct TYPE_8__ {int serial_signals; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ MGSLPC_INFO ;

/* Variables and functions */
 int CBAUD ; 
 int CRTSCTS ; 
 scalar_t__ C_BAUD (struct tty_struct*) ; 
 int /*<<< orphan*/  C_CRTSCTS (struct tty_struct*) ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ RELEVANT_IFLAG (int /*<<< orphan*/ ) ; 
 int SerialSignal_DTR ; 
 int SerialSignal_RTS ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  mgslpc_change_params (TYPE_3__*,struct tty_struct*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_signals (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_throttled (struct tty_struct*) ; 
 int /*<<< orphan*/  tx_release (struct tty_struct*) ; 

__attribute__((used)) static void mgslpc_set_termios(struct tty_struct *tty, struct ktermios *old_termios)
{
	MGSLPC_INFO *info = (MGSLPC_INFO *)tty->driver_data;
	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgslpc_set_termios %s\n", __FILE__, __LINE__,
			tty->driver->name);

	/* just return if nothing has changed */
	if ((tty->termios.c_cflag == old_termios->c_cflag)
	    && (RELEVANT_IFLAG(tty->termios.c_iflag)
		== RELEVANT_IFLAG(old_termios->c_iflag)))
	  return;

	mgslpc_change_params(info, tty);

	/* Handle transition to B0 status */
	if ((old_termios->c_cflag & CBAUD) && !C_BAUD(tty)) {
		info->serial_signals &= ~(SerialSignal_RTS | SerialSignal_DTR);
		spin_lock_irqsave(&info->lock, flags);
		set_signals(info);
		spin_unlock_irqrestore(&info->lock, flags);
	}

	/* Handle transition away from B0 status */
	if (!(old_termios->c_cflag & CBAUD) && C_BAUD(tty)) {
		info->serial_signals |= SerialSignal_DTR;
		if (!C_CRTSCTS(tty) || !tty_throttled(tty))
			info->serial_signals |= SerialSignal_RTS;
		spin_lock_irqsave(&info->lock, flags);
		set_signals(info);
		spin_unlock_irqrestore(&info->lock, flags);
	}

	/* Handle turning off CRTSCTS */
	if (old_termios->c_cflag & CRTSCTS && !C_CRTSCTS(tty)) {
		tty->hw_stopped = 0;
		tx_release(tty);
	}
}