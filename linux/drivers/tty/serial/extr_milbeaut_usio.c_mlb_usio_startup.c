#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int line; int /*<<< orphan*/  lock; scalar_t__ membase; TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int BIT (int) ; 
 unsigned char MLB_USIO_ESCR_FLWEN ; 
 int MLB_USIO_FCR_FCL1 ; 
 int MLB_USIO_FCR_FCL2 ; 
 int MLB_USIO_FCR_FE1 ; 
 int MLB_USIO_FCR_FE2 ; 
 int MLB_USIO_FCR_FRIIE ; 
 scalar_t__ MLB_USIO_REG_ESCR ; 
 scalar_t__ MLB_USIO_REG_FBYTE ; 
 scalar_t__ MLB_USIO_REG_FCR ; 
 scalar_t__ MLB_USIO_REG_SCR ; 
 scalar_t__ MLB_USIO_REG_SSR ; 
 unsigned char MLB_USIO_SCR_RIE ; 
 unsigned char MLB_USIO_SCR_RXE ; 
 unsigned char MLB_USIO_SCR_TBIE ; 
 unsigned char MLB_USIO_SCR_TXE ; 
 unsigned char MLB_USIO_SCR_UPCL ; 
 unsigned char MLB_USIO_SSR_REC ; 
 size_t RX ; 
 size_t TX ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/ ** mlb_usio_irq ; 
 int /*<<< orphan*/  mlb_usio_rx_irq ; 
 int /*<<< orphan*/  mlb_usio_tx_irq ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 unsigned char readb (scalar_t__) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* to_platform_device (TYPE_2__*) ; 
 int /*<<< orphan*/  writeb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int mlb_usio_startup(struct uart_port *port)
{
	const char *portname = to_platform_device(port->dev)->name;
	unsigned long flags;
	int ret, index = port->line;
	unsigned char  escr;

	ret = request_irq(mlb_usio_irq[index][RX], mlb_usio_rx_irq,
				0, portname, port);
	if (ret)
		return ret;
	ret = request_irq(mlb_usio_irq[index][TX], mlb_usio_tx_irq,
				0, portname, port);
	if (ret) {
		free_irq(mlb_usio_irq[index][RX], port);
		return ret;
	}

	escr = readb(port->membase + MLB_USIO_REG_ESCR);
	if (of_property_read_bool(port->dev->of_node, "auto-flow-control"))
		escr |= MLB_USIO_ESCR_FLWEN;
	spin_lock_irqsave(&port->lock, flags);
	writeb(0, port->membase + MLB_USIO_REG_SCR);
	writeb(escr, port->membase + MLB_USIO_REG_ESCR);
	writeb(MLB_USIO_SCR_UPCL, port->membase + MLB_USIO_REG_SCR);
	writeb(MLB_USIO_SSR_REC, port->membase + MLB_USIO_REG_SSR);
	writew(0, port->membase + MLB_USIO_REG_FCR);
	writew(MLB_USIO_FCR_FCL1 | MLB_USIO_FCR_FCL2,
	       port->membase + MLB_USIO_REG_FCR);
	writew(MLB_USIO_FCR_FE1 | MLB_USIO_FCR_FE2 | MLB_USIO_FCR_FRIIE,
	       port->membase + MLB_USIO_REG_FCR);
	writew(0, port->membase + MLB_USIO_REG_FBYTE);
	writew(BIT(12), port->membase + MLB_USIO_REG_FBYTE);

	writeb(MLB_USIO_SCR_TXE  | MLB_USIO_SCR_RIE | MLB_USIO_SCR_TBIE |
	       MLB_USIO_SCR_RXE, port->membase + MLB_USIO_REG_SCR);
	spin_unlock_irqrestore(&port->lock, flags);

	return 0;
}