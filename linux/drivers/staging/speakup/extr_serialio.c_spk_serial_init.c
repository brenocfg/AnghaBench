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
struct old_serial_port {int baud_base; int /*<<< orphan*/  irq; scalar_t__ port; } ;
struct TYPE_2__ {scalar_t__ port_tts; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct old_serial_port*) ; 
 int B9600 ; 
 int CLOCAL ; 
 int CREAD ; 
 int CS8 ; 
 int CSIZE ; 
 int CSTOPB ; 
 int HUPCL ; 
 int PARENB ; 
 int PARODD ; 
 scalar_t__ UART_DLL ; 
 scalar_t__ UART_DLM ; 
 scalar_t__ UART_IER ; 
 scalar_t__ UART_LCR ; 
 unsigned int UART_LCR_DLAB ; 
 unsigned int UART_LCR_EPAR ; 
 unsigned int UART_LCR_PARITY ; 
 scalar_t__ UART_LSR ; 
 scalar_t__ UART_MCR ; 
 unsigned int UART_MCR_DTR ; 
 unsigned int UART_MCR_RTS ; 
 int /*<<< orphan*/  __release_region (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  ioport_resource ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,int) ; 
 struct old_serial_port* rs_table ; 
 struct old_serial_port const* serstate ; 
 TYPE_1__ speakup_info ; 
 int /*<<< orphan*/  start_serial_interrupt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synth_release_region (scalar_t__,int) ; 
 int synth_request_region (scalar_t__,int) ; 

const struct old_serial_port *spk_serial_init(int index)
{
	int baud = 9600, quot = 0;
	unsigned int cval = 0;
	int cflag = CREAD | HUPCL | CLOCAL | B9600 | CS8;
	const struct old_serial_port *ser;
	int err;

	if (index >= ARRAY_SIZE(rs_table)) {
		pr_info("no port info for ttyS%d\n", index);
		return NULL;
	}
	ser = rs_table + index;

	/*	Divisor, bytesize and parity */
	quot = ser->baud_base / baud;
	cval = cflag & (CSIZE | CSTOPB);
#if defined(__powerpc__) || defined(__alpha__)
	cval >>= 8;
#else /* !__powerpc__ && !__alpha__ */
	cval >>= 4;
#endif /* !__powerpc__ && !__alpha__ */
	if (cflag & PARENB)
		cval |= UART_LCR_PARITY;
	if (!(cflag & PARODD))
		cval |= UART_LCR_EPAR;
	if (synth_request_region(ser->port, 8)) {
		/* try to take it back. */
		pr_info("Ports not available, trying to steal them\n");
		__release_region(&ioport_resource, ser->port, 8);
		err = synth_request_region(ser->port, 8);
		if (err) {
			pr_warn("Unable to allocate port at %x, errno %i",
				ser->port, err);
			return NULL;
		}
	}

	/*	Disable UART interrupts, set DTR and RTS high
	 *	and set speed.
	 */
	outb(cval | UART_LCR_DLAB, ser->port + UART_LCR);	/* set DLAB */
	outb(quot & 0xff, ser->port + UART_DLL);	/* LS of divisor */
	outb(quot >> 8, ser->port + UART_DLM);		/* MS of divisor */
	outb(cval, ser->port + UART_LCR);		/* reset DLAB */

	/* Turn off Interrupts */
	outb(0, ser->port + UART_IER);
	outb(UART_MCR_DTR | UART_MCR_RTS, ser->port + UART_MCR);

	/* If we read 0xff from the LSR, there is no UART here. */
	if (inb(ser->port + UART_LSR) == 0xff) {
		synth_release_region(ser->port, 8);
		serstate = NULL;
		return NULL;
	}

	mdelay(1);
	speakup_info.port_tts = ser->port;
	serstate = ser;

	start_serial_interrupt(ser->irq);

	return ser;
}