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
struct uart_port {int read_status_mask; int /*<<< orphan*/  lock; scalar_t__ membase; int /*<<< orphan*/  ignore_status_mask; } ;
struct ktermios {unsigned int c_cflag; int c_iflag; } ;

/* Variables and functions */
 int BRKINT ; 
 int CMSPAR ; 
 unsigned int CS7 ; 
 unsigned int CS8 ; 
 unsigned int CSIZE ; 
 int CSTOPB ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 scalar_t__ LINCR1 ; 
 unsigned long LINFLEXD_LINCR1_INIT ; 
 unsigned long LINFLEXD_LINSR_LINS_INITMODE ; 
 unsigned long LINFLEXD_LINSR_LINS_MASK ; 
 unsigned long LINFLEXD_UARTCR_PC0 ; 
 unsigned long LINFLEXD_UARTCR_PC1 ; 
 unsigned long LINFLEXD_UARTCR_PCE ; 
 unsigned long LINFLEXD_UARTCR_WL0 ; 
 unsigned long LINFLEXD_UARTCR_WL1 ; 
 int /*<<< orphan*/  LINFLEXD_UARTSR_BOF ; 
 int LINFLEXD_UARTSR_FEF ; 
 int /*<<< orphan*/  LINFLEXD_UARTSR_PE ; 
 int LINFLEXD_UARTSR_PE0 ; 
 int LINFLEXD_UARTSR_PE1 ; 
 int LINFLEXD_UARTSR_PE2 ; 
 int LINFLEXD_UARTSR_PE3 ; 
 scalar_t__ LINSR ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 scalar_t__ UARTCR ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void
linflex_set_termios(struct uart_port *port, struct ktermios *termios,
		    struct ktermios *old)
{
	unsigned long flags;
	unsigned long cr, old_cr, cr1;
	unsigned int old_csize = old ? old->c_cflag & CSIZE : CS8;

	cr = readl(port->membase + UARTCR);
	old_cr = cr;

	/* Enter initialization mode by setting INIT bit */
	cr1 = readl(port->membase + LINCR1);
	cr1 |= LINFLEXD_LINCR1_INIT;
	writel(cr1, port->membase + LINCR1);

	/* wait for init mode entry */
	while ((readl(port->membase + LINSR)
		& LINFLEXD_LINSR_LINS_MASK)
		!= LINFLEXD_LINSR_LINS_INITMODE)
		;

	/*
	 * only support CS8 and CS7, and for CS7 must enable PE.
	 * supported mode:
	 *	- (7,e/o,1)
	 *	- (8,n,1)
	 *	- (8,e/o,1)
	 */
	/* enter the UART into configuration mode */

	while ((termios->c_cflag & CSIZE) != CS8 &&
	       (termios->c_cflag & CSIZE) != CS7) {
		termios->c_cflag &= ~CSIZE;
		termios->c_cflag |= old_csize;
		old_csize = CS8;
	}

	if ((termios->c_cflag & CSIZE) == CS7) {
		/* Word length: WL1WL0:00 */
		cr = old_cr & ~LINFLEXD_UARTCR_WL1 & ~LINFLEXD_UARTCR_WL0;
	}

	if ((termios->c_cflag & CSIZE) == CS8) {
		/* Word length: WL1WL0:01 */
		cr = (old_cr | LINFLEXD_UARTCR_WL0) & ~LINFLEXD_UARTCR_WL1;
	}

	if (termios->c_cflag & CMSPAR) {
		if ((termios->c_cflag & CSIZE) != CS8) {
			termios->c_cflag &= ~CSIZE;
			termios->c_cflag |= CS8;
		}
		/* has a space/sticky bit */
		cr |= LINFLEXD_UARTCR_WL0;
	}

	if (termios->c_cflag & CSTOPB)
		termios->c_cflag &= ~CSTOPB;

	/* parity must be enabled when CS7 to match 8-bits format */
	if ((termios->c_cflag & CSIZE) == CS7)
		termios->c_cflag |= PARENB;

	if ((termios->c_cflag & PARENB)) {
		cr |= LINFLEXD_UARTCR_PCE;
		if (termios->c_cflag & PARODD)
			cr = (cr | LINFLEXD_UARTCR_PC0) &
			     (~LINFLEXD_UARTCR_PC1);
		else
			cr = cr & (~LINFLEXD_UARTCR_PC1 &
				   ~LINFLEXD_UARTCR_PC0);
	} else {
		cr &= ~LINFLEXD_UARTCR_PCE;
	}

	spin_lock_irqsave(&port->lock, flags);

	port->read_status_mask = 0;

	if (termios->c_iflag & INPCK)
		port->read_status_mask |=	(LINFLEXD_UARTSR_FEF |
						 LINFLEXD_UARTSR_PE0 |
						 LINFLEXD_UARTSR_PE1 |
						 LINFLEXD_UARTSR_PE2 |
						 LINFLEXD_UARTSR_PE3);
	if (termios->c_iflag & (IGNBRK | BRKINT | PARMRK))
		port->read_status_mask |= LINFLEXD_UARTSR_FEF;

	/* characters to ignore */
	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		port->ignore_status_mask |= LINFLEXD_UARTSR_PE;
	if (termios->c_iflag & IGNBRK) {
		port->ignore_status_mask |= LINFLEXD_UARTSR_PE;
		/*
		 * if we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			port->ignore_status_mask |= LINFLEXD_UARTSR_BOF;
	}

	writel(cr, port->membase + UARTCR);

	cr1 &= ~(LINFLEXD_LINCR1_INIT);

	writel(cr1, port->membase + LINCR1);

	spin_unlock_irqrestore(&port->lock, flags);
}