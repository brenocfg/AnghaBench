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
struct uart_port {int iotype; unsigned long long iobase; int uartclk; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; scalar_t__ dev; scalar_t__ mapbase; int /*<<< orphan*/  hub6; } ;
struct uart_driver {int dummy; } ;
typedef  int /*<<< orphan*/  address ;

/* Variables and functions */
#define  UPIO_AU 135 
#define  UPIO_HUB6 134 
#define  UPIO_MEM 133 
#define  UPIO_MEM16 132 
#define  UPIO_MEM32 131 
#define  UPIO_MEM32BE 130 
#define  UPIO_PORT 129 
#define  UPIO_TSI 128 
 char* dev_name (scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  uart_type (struct uart_port*) ; 

__attribute__((used)) static inline void
uart_report_port(struct uart_driver *drv, struct uart_port *port)
{
	char address[64];

	switch (port->iotype) {
	case UPIO_PORT:
		snprintf(address, sizeof(address), "I/O 0x%lx", port->iobase);
		break;
	case UPIO_HUB6:
		snprintf(address, sizeof(address),
			 "I/O 0x%lx offset 0x%x", port->iobase, port->hub6);
		break;
	case UPIO_MEM:
	case UPIO_MEM16:
	case UPIO_MEM32:
	case UPIO_MEM32BE:
	case UPIO_AU:
	case UPIO_TSI:
		snprintf(address, sizeof(address),
			 "MMIO 0x%llx", (unsigned long long)port->mapbase);
		break;
	default:
		strlcpy(address, "*unknown*", sizeof(address));
		break;
	}

	pr_info("%s%s%s at %s (irq = %d, base_baud = %d) is a %s\n",
	       port->dev ? dev_name(port->dev) : "",
	       port->dev ? ": " : "",
	       port->name,
	       address, port->irq, port->uartclk / 16, uart_type(port));
}