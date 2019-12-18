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
typedef  int u8 ;

/* Variables and functions */
 int ENODEV ; 
 int UART_DLL ; 
 int UART_DLM ; 
 int UART_FCR ; 
 int UART_FCR_ENABLE_FIFO ; 
 int UART_IER ; 
 int UART_IER_RDI ; 
 int UART_LCR ; 
 int UART_LCR_DLAB ; 
 int UART_LCR_WLEN7 ; 
 int UART_MCR ; 
 int UART_MCR_DTR ; 
 int UART_MCR_OUT2 ; 
 int UART_MCR_RTS ; 
 int /*<<< orphan*/  hardware_lock ; 
 int io ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int sinp (int) ; 
 int /*<<< orphan*/  soutp (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int init_hardware(void)
{
	u8 scratch, scratch2, scratch3;
	unsigned long flags;

	spin_lock_irqsave(&hardware_lock, flags);

	/*
	 * This is a simple port existence test, borrowed from the autoconfig
	 * function in drivers/tty/serial/8250/8250_port.c
	 */
	scratch = sinp(UART_IER);
	soutp(UART_IER, 0);
#ifdef __i386__
	outb(0xff, 0x080);
#endif
	scratch2 = sinp(UART_IER) & 0x0f;
	soutp(UART_IER, 0x0f);
#ifdef __i386__
	outb(0x00, 0x080);
#endif
	scratch3 = sinp(UART_IER) & 0x0f;
	soutp(UART_IER, scratch);
	if (scratch2 != 0 || scratch3 != 0x0f) {
		/* we fail, there's nothing here */
		spin_unlock_irqrestore(&hardware_lock, flags);
		pr_err("port existence test failed, cannot continue\n");
		return -ENODEV;
	}

	/* reset UART */
	outb(0, io + UART_MCR);
	outb(0, io + UART_IER);
	/* init UART */
	/* set DLAB, speed = 115200 */
	outb(UART_LCR_DLAB | UART_LCR_WLEN7, io + UART_LCR);
	outb(1, io + UART_DLL); outb(0, io + UART_DLM);
	/* 7N1+start = 9 bits at 115200 ~ 3 bits at 44000 */
	outb(UART_LCR_WLEN7, io + UART_LCR);
	/* FIFO operation */
	outb(UART_FCR_ENABLE_FIFO, io + UART_FCR);
	/* interrupts */
	/* outb(UART_IER_RLSI|UART_IER_RDI|UART_IER_THRI, io + UART_IER); */
	outb(UART_IER_RDI, io + UART_IER);
	/* turn on UART */
	outb(UART_MCR_DTR | UART_MCR_RTS | UART_MCR_OUT2, io + UART_MCR);
	spin_unlock_irqrestore(&hardware_lock, flags);

	return 0;
}