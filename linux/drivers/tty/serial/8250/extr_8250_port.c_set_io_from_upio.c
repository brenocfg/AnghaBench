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
struct uart_port {int iotype; int /*<<< orphan*/  handle_irq; int /*<<< orphan*/  serial_out; int /*<<< orphan*/  serial_in; } ;
struct uart_8250_port {int cur_iotype; int /*<<< orphan*/  dl_write; int /*<<< orphan*/  dl_read; } ;

/* Variables and functions */
#define  UPIO_AU 133 
#define  UPIO_HUB6 132 
#define  UPIO_MEM 131 
#define  UPIO_MEM16 130 
#define  UPIO_MEM32 129 
#define  UPIO_MEM32BE 128 
 int /*<<< orphan*/  au_serial_dl_read ; 
 int /*<<< orphan*/  au_serial_dl_write ; 
 int /*<<< orphan*/  au_serial_in ; 
 int /*<<< orphan*/  au_serial_out ; 
 int /*<<< orphan*/  default_serial_dl_read ; 
 int /*<<< orphan*/  default_serial_dl_write ; 
 int /*<<< orphan*/  hub6_serial_in ; 
 int /*<<< orphan*/  hub6_serial_out ; 
 int /*<<< orphan*/  io_serial_in ; 
 int /*<<< orphan*/  io_serial_out ; 
 int /*<<< orphan*/  mem16_serial_in ; 
 int /*<<< orphan*/  mem16_serial_out ; 
 int /*<<< orphan*/  mem32_serial_in ; 
 int /*<<< orphan*/  mem32_serial_out ; 
 int /*<<< orphan*/  mem32be_serial_in ; 
 int /*<<< orphan*/  mem32be_serial_out ; 
 int /*<<< orphan*/  mem_serial_in ; 
 int /*<<< orphan*/  mem_serial_out ; 
 int /*<<< orphan*/  serial8250_default_handle_irq ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static void set_io_from_upio(struct uart_port *p)
{
	struct uart_8250_port *up = up_to_u8250p(p);

	up->dl_read = default_serial_dl_read;
	up->dl_write = default_serial_dl_write;

	switch (p->iotype) {
	case UPIO_HUB6:
		p->serial_in = hub6_serial_in;
		p->serial_out = hub6_serial_out;
		break;

	case UPIO_MEM:
		p->serial_in = mem_serial_in;
		p->serial_out = mem_serial_out;
		break;

	case UPIO_MEM16:
		p->serial_in = mem16_serial_in;
		p->serial_out = mem16_serial_out;
		break;

	case UPIO_MEM32:
		p->serial_in = mem32_serial_in;
		p->serial_out = mem32_serial_out;
		break;

	case UPIO_MEM32BE:
		p->serial_in = mem32be_serial_in;
		p->serial_out = mem32be_serial_out;
		break;

#ifdef CONFIG_SERIAL_8250_RT288X
	case UPIO_AU:
		p->serial_in = au_serial_in;
		p->serial_out = au_serial_out;
		up->dl_read = au_serial_dl_read;
		up->dl_write = au_serial_dl_write;
		break;
#endif

	default:
		p->serial_in = io_serial_in;
		p->serial_out = io_serial_out;
		break;
	}
	/* Remember loaded iotype */
	up->cur_iotype = p->iotype;
	p->handle_irq = serial8250_default_handle_irq;
}