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
struct TYPE_2__ {scalar_t__ type; int uartclk; } ;
struct uart_8250_port {int capabilities; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_AUTOCONF (char*,...) ; 
 scalar_t__ PORT_16550A ; 
 scalar_t__ PORT_16550A_FSL64 ; 
 scalar_t__ PORT_16650 ; 
 scalar_t__ PORT_16750 ; 
 scalar_t__ PORT_NS16550A ; 
 scalar_t__ PORT_U6_16550A ; 
 scalar_t__ PORT_XSCALE ; 
 int UART_CAP_AFE ; 
 int UART_CAP_EFR ; 
 int UART_CAP_FIFO ; 
 int UART_CAP_RTOIE ; 
 int UART_CAP_SLEEP ; 
 int UART_CAP_UUE ; 
 int UART_EFR ; 
 int UART_FCR ; 
 unsigned int UART_FCR7_64BYTE ; 
 unsigned int UART_FCR_ENABLE_FIFO ; 
 int UART_IER ; 
 unsigned int UART_IER_UUE ; 
 int UART_IIR ; 
 int UART_LCR ; 
 unsigned int UART_LCR_CONF_MODE_A ; 
 unsigned int UART_LCR_CONF_MODE_B ; 
 unsigned char UART_MCR_LOOP ; 
 int UART_NATSEMI ; 
 int /*<<< orphan*/  autoconfig_has_efr (struct uart_8250_port*) ; 
 int /*<<< orphan*/  broken_efr (struct uart_8250_port*) ; 
 scalar_t__ ns16550a_goto_highspeed (struct uart_8250_port*) ; 
 unsigned char serial8250_in_MCR (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_out_MCR (struct uart_8250_port*,unsigned char) ; 
 unsigned short serial_dl_read (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial_dl_write (struct uart_8250_port*,unsigned short) ; 
 unsigned int serial_in (struct uart_8250_port*,int) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int,unsigned int) ; 
 int size_fifo (struct uart_8250_port*) ; 

__attribute__((used)) static void autoconfig_16550a(struct uart_8250_port *up)
{
	unsigned char status1, status2;
	unsigned int iersave;

	up->port.type = PORT_16550A;
	up->capabilities |= UART_CAP_FIFO;

	/*
	 * Check for presence of the EFR when DLAB is set.
	 * Only ST16C650V1 UARTs pass this test.
	 */
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	if (serial_in(up, UART_EFR) == 0) {
		serial_out(up, UART_EFR, 0xA8);
		if (serial_in(up, UART_EFR) != 0) {
			DEBUG_AUTOCONF("EFRv1 ");
			up->port.type = PORT_16650;
			up->capabilities |= UART_CAP_EFR | UART_CAP_SLEEP;
		} else {
			serial_out(up, UART_LCR, 0);
			serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO |
				   UART_FCR7_64BYTE);
			status1 = serial_in(up, UART_IIR) >> 5;
			serial_out(up, UART_FCR, 0);
			serial_out(up, UART_LCR, 0);

			if (status1 == 7)
				up->port.type = PORT_16550A_FSL64;
			else
				DEBUG_AUTOCONF("Motorola 8xxx DUART ");
		}
		serial_out(up, UART_EFR, 0);
		return;
	}

	/*
	 * Maybe it requires 0xbf to be written to the LCR.
	 * (other ST16C650V2 UARTs, TI16C752A, etc)
	 */
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	if (serial_in(up, UART_EFR) == 0 && !broken_efr(up)) {
		DEBUG_AUTOCONF("EFRv2 ");
		autoconfig_has_efr(up);
		return;
	}

	/*
	 * Check for a National Semiconductor SuperIO chip.
	 * Attempt to switch to bank 2, read the value of the LOOP bit
	 * from EXCR1. Switch back to bank 0, change it in MCR. Then
	 * switch back to bank 2, read it from EXCR1 again and check
	 * it's changed. If so, set baud_base in EXCR2 to 921600. -- dwmw2
	 */
	serial_out(up, UART_LCR, 0);
	status1 = serial8250_in_MCR(up);
	serial_out(up, UART_LCR, 0xE0);
	status2 = serial_in(up, 0x02); /* EXCR1 */

	if (!((status2 ^ status1) & UART_MCR_LOOP)) {
		serial_out(up, UART_LCR, 0);
		serial8250_out_MCR(up, status1 ^ UART_MCR_LOOP);
		serial_out(up, UART_LCR, 0xE0);
		status2 = serial_in(up, 0x02); /* EXCR1 */
		serial_out(up, UART_LCR, 0);
		serial8250_out_MCR(up, status1);

		if ((status2 ^ status1) & UART_MCR_LOOP) {
			unsigned short quot;

			serial_out(up, UART_LCR, 0xE0);

			quot = serial_dl_read(up);
			quot <<= 3;

			if (ns16550a_goto_highspeed(up))
				serial_dl_write(up, quot);

			serial_out(up, UART_LCR, 0);

			up->port.uartclk = 921600*16;
			up->port.type = PORT_NS16550A;
			up->capabilities |= UART_NATSEMI;
			return;
		}
	}

	/*
	 * No EFR.  Try to detect a TI16750, which only sets bit 5 of
	 * the IIR when 64 byte FIFO mode is enabled when DLAB is set.
	 * Try setting it with and without DLAB set.  Cheap clones
	 * set bit 5 without DLAB set.
	 */
	serial_out(up, UART_LCR, 0);
	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO | UART_FCR7_64BYTE);
	status1 = serial_in(up, UART_IIR) >> 5;
	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO | UART_FCR7_64BYTE);
	status2 = serial_in(up, UART_IIR) >> 5;
	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO);
	serial_out(up, UART_LCR, 0);

	DEBUG_AUTOCONF("iir1=%d iir2=%d ", status1, status2);

	if (status1 == 6 && status2 == 7) {
		up->port.type = PORT_16750;
		up->capabilities |= UART_CAP_AFE | UART_CAP_SLEEP;
		return;
	}

	/*
	 * Try writing and reading the UART_IER_UUE bit (b6).
	 * If it works, this is probably one of the Xscale platform's
	 * internal UARTs.
	 * We're going to explicitly set the UUE bit to 0 before
	 * trying to write and read a 1 just to make sure it's not
	 * already a 1 and maybe locked there before we even start start.
	 */
	iersave = serial_in(up, UART_IER);
	serial_out(up, UART_IER, iersave & ~UART_IER_UUE);
	if (!(serial_in(up, UART_IER) & UART_IER_UUE)) {
		/*
		 * OK it's in a known zero state, try writing and reading
		 * without disturbing the current state of the other bits.
		 */
		serial_out(up, UART_IER, iersave | UART_IER_UUE);
		if (serial_in(up, UART_IER) & UART_IER_UUE) {
			/*
			 * It's an Xscale.
			 * We'll leave the UART_IER_UUE bit set to 1 (enabled).
			 */
			DEBUG_AUTOCONF("Xscale ");
			up->port.type = PORT_XSCALE;
			up->capabilities |= UART_CAP_UUE | UART_CAP_RTOIE;
			return;
		}
	} else {
		/*
		 * If we got here we couldn't force the IER_UUE bit to 0.
		 * Log it and continue.
		 */
		DEBUG_AUTOCONF("Couldn't force IER_UUE to 0 ");
	}
	serial_out(up, UART_IER, iersave);

	/*
	 * We distinguish between 16550A and U6 16550A by counting
	 * how many bytes are in the FIFO.
	 */
	if (up->port.type == PORT_16550A && size_fifo(up) == 64) {
		up->port.type = PORT_U6_16550A;
		up->capabilities |= UART_CAP_AFE;
	}
}