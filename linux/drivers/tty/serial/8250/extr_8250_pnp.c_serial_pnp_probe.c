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
typedef  int /*<<< orphan*/  uart ;
struct TYPE_2__ {int flags; int uartclk; int /*<<< orphan*/ * dev; int /*<<< orphan*/  type; void* iotype; int /*<<< orphan*/  irq; scalar_t__ mapbase; void* iobase; } ;
struct uart_8250_port {TYPE_1__ port; } ;
struct pnp_device_id {int driver_data; } ;
struct pnp_dev {int /*<<< orphan*/  capabilities; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CIR_PORT ; 
 int ENODEV ; 
 int IORESOURCE_IRQ_SHAREABLE ; 
 int /*<<< orphan*/  PNP_CONSOLE ; 
 int /*<<< orphan*/  PORT_8250_CIR ; 
 int UNKNOWN_DEV ; 
 int UPF_BOOT_AUTOCONF ; 
 int UPF_FIXED_PORT ; 
 int UPF_FIXED_TYPE ; 
 int UPF_IOREMAP ; 
 int UPF_SHARE_IRQ ; 
 int UPF_SKIP_TEST ; 
 void* UPIO_MEM ; 
 void* UPIO_PORT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,void*,unsigned long long,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memset (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pnp_irq (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int pnp_irq_flags (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pnp_irq_valid (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pnp_mem_start (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pnp_mem_valid (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 void* pnp_port_start (struct pnp_dev*,int) ; 
 scalar_t__ pnp_port_valid (struct pnp_dev*,int) ; 
 int /*<<< orphan*/  pnp_set_drvdata (struct pnp_dev*,void*) ; 
 struct uart_8250_port* serial8250_get_port (int) ; 
 int serial8250_register_8250_port (struct uart_8250_port*) ; 
 int serial_pnp_guess_board (struct pnp_dev*) ; 
 scalar_t__ uart_console (TYPE_1__*) ; 

__attribute__((used)) static int
serial_pnp_probe(struct pnp_dev *dev, const struct pnp_device_id *dev_id)
{
	struct uart_8250_port uart, *port;
	int ret, line, flags = dev_id->driver_data;

	if (flags & UNKNOWN_DEV) {
		ret = serial_pnp_guess_board(dev);
		if (ret < 0)
			return ret;
	}

	memset(&uart, 0, sizeof(uart));
	if (pnp_irq_valid(dev, 0))
		uart.port.irq = pnp_irq(dev, 0);
	if ((flags & CIR_PORT) && pnp_port_valid(dev, 2)) {
		uart.port.iobase = pnp_port_start(dev, 2);
		uart.port.iotype = UPIO_PORT;
	} else if (pnp_port_valid(dev, 0)) {
		uart.port.iobase = pnp_port_start(dev, 0);
		uart.port.iotype = UPIO_PORT;
	} else if (pnp_mem_valid(dev, 0)) {
		uart.port.mapbase = pnp_mem_start(dev, 0);
		uart.port.iotype = UPIO_MEM;
		uart.port.flags = UPF_IOREMAP;
	} else
		return -ENODEV;

	dev_dbg(&dev->dev,
		 "Setup PNP port: port %#lx, mem %#llx, irq %u, type %u\n",
		 uart.port.iobase, (unsigned long long)uart.port.mapbase,
		 uart.port.irq, uart.port.iotype);

	if (flags & CIR_PORT) {
		uart.port.flags |= UPF_FIXED_PORT | UPF_FIXED_TYPE;
		uart.port.type = PORT_8250_CIR;
	}

	uart.port.flags |= UPF_SKIP_TEST | UPF_BOOT_AUTOCONF;
	if (pnp_irq_flags(dev, 0) & IORESOURCE_IRQ_SHAREABLE)
		uart.port.flags |= UPF_SHARE_IRQ;
	uart.port.uartclk = 1843200;
	uart.port.dev = &dev->dev;

	line = serial8250_register_8250_port(&uart);
	if (line < 0 || (flags & CIR_PORT))
		return -ENODEV;

	port = serial8250_get_port(line);
	if (uart_console(&port->port))
		dev->capabilities |= PNP_CONSOLE;

	pnp_set_drvdata(dev, (void *)((long)line + 1));
	return 0;
}