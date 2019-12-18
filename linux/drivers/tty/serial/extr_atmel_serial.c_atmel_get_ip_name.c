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
typedef  int u32 ;
struct uart_port {int /*<<< orphan*/  dev; } ;
struct atmel_uart_port {int has_frac_baudrate; int has_hw_timer; int fidi_min; int fidi_max; void* rtor; } ;

/* Variables and functions */
 void* ATMEL_UA_RTOR ; 
 int /*<<< orphan*/  ATMEL_US_NAME ; 
 void* ATMEL_US_RTOR ; 
 int /*<<< orphan*/  ATMEL_US_VERSION ; 
 int atmel_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void atmel_get_ip_name(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	int name = atmel_uart_readl(port, ATMEL_US_NAME);
	u32 version;
	u32 usart, dbgu_uart, new_uart;
	/* ASCII decoding for IP version */
	usart = 0x55534152;	/* USAR(T) */
	dbgu_uart = 0x44424755;	/* DBGU */
	new_uart = 0x55415254;	/* UART */

	/*
	 * Only USART devices from at91sam9260 SOC implement fractional
	 * baudrate. It is available for all asynchronous modes, with the
	 * following restriction: the sampling clock's duty cycle is not
	 * constant.
	 */
	atmel_port->has_frac_baudrate = false;
	atmel_port->has_hw_timer = false;

	if (name == new_uart) {
		dev_dbg(port->dev, "Uart with hw timer");
		atmel_port->has_hw_timer = true;
		atmel_port->rtor = ATMEL_UA_RTOR;
	} else if (name == usart) {
		dev_dbg(port->dev, "Usart\n");
		atmel_port->has_frac_baudrate = true;
		atmel_port->has_hw_timer = true;
		atmel_port->rtor = ATMEL_US_RTOR;
		version = atmel_uart_readl(port, ATMEL_US_VERSION);
		switch (version) {
		case 0x814:	/* sama5d2 */
			/* fall through */
		case 0x701:	/* sama5d4 */
			atmel_port->fidi_min = 3;
			atmel_port->fidi_max = 65535;
			break;
		case 0x502:	/* sam9x5, sama5d3 */
			atmel_port->fidi_min = 3;
			atmel_port->fidi_max = 2047;
			break;
		default:
			atmel_port->fidi_min = 1;
			atmel_port->fidi_max = 2047;
		}
	} else if (name == dbgu_uart) {
		dev_dbg(port->dev, "Dbgu or uart without hw timer\n");
	} else {
		/* fallback for older SoCs: use version field */
		version = atmel_uart_readl(port, ATMEL_US_VERSION);
		switch (version) {
		case 0x302:
		case 0x10213:
		case 0x10302:
			dev_dbg(port->dev, "This version is usart\n");
			atmel_port->has_frac_baudrate = true;
			atmel_port->has_hw_timer = true;
			atmel_port->rtor = ATMEL_US_RTOR;
			break;
		case 0x203:
		case 0x10202:
			dev_dbg(port->dev, "This version is uart\n");
			break;
		default:
			dev_err(port->dev, "Not supported ip name nor version, set to uart\n");
		}
	}
}