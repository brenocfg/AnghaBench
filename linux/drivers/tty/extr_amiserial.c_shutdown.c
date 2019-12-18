#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_5__ {int /*<<< orphan*/ * buf; } ;
struct serial_state {int MCR; TYPE_2__ tport; scalar_t__ IER; TYPE_1__ xmit; int /*<<< orphan*/  line; } ;
struct TYPE_7__ {int intena; int /*<<< orphan*/  adkcon; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_UARTBRK ; 
 scalar_t__ C_HUPCL (struct tty_struct*) ; 
 int IF_RBF ; 
 int IF_TBE ; 
 int /*<<< orphan*/  IRQ_AMIGA_VERTB ; 
 int SER_DTR ; 
 int SER_RTS ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 TYPE_4__ custom ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct serial_state*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsdtr_ctrl (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_initialized (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shutdown(struct tty_struct *tty, struct serial_state *info)
{
	unsigned long	flags;
	struct serial_state *state;

	if (!tty_port_initialized(&info->tport))
		return;

	state = info;

#ifdef SERIAL_DEBUG_OPEN
	printk("Shutting down serial port %d ....\n", info->line);
#endif

	local_irq_save(flags); /* Disable interrupts */

	/*
	 * clear delta_msr_wait queue to avoid mem leaks: we may free the irq
	 * here so the queue might never be waken up
	 */
	wake_up_interruptible(&info->tport.delta_msr_wait);

	/*
	 * Free the IRQ, if necessary
	 */
	free_irq(IRQ_AMIGA_VERTB, info);

	if (info->xmit.buf) {
		free_page((unsigned long) info->xmit.buf);
		info->xmit.buf = NULL;
	}

	info->IER = 0;
	custom.intena = IF_RBF | IF_TBE;
	mb();

	/* disable break condition */
	custom.adkcon = AC_UARTBRK;
	mb();

	if (C_HUPCL(tty))
		info->MCR &= ~(SER_DTR|SER_RTS);
	rtsdtr_ctrl(info->MCR);

	set_bit(TTY_IO_ERROR, &tty->flags);

	tty_port_set_initialized(&info->tport, 0);
	local_irq_restore(flags);
}