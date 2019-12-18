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
struct uart_8250_port {int dummy; } ;
struct serial_private {int dummy; } ;
struct pciserial_board {unsigned int first_offset; int uart_offset; int /*<<< orphan*/  reg_shift; } ;

/* Variables and functions */
 int setup_port (struct serial_private*,struct uart_8250_port*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sbs_setup(struct serial_private *priv, const struct pciserial_board *board,
		struct uart_8250_port *port, int idx)
{
	unsigned int bar, offset = board->first_offset;

	bar = 0;

	if (idx < 4) {
		/* first four channels map to 0, 0x100, 0x200, 0x300 */
		offset += idx * board->uart_offset;
	} else if (idx < 8) {
		/* last four channels map to 0x1000, 0x1100, 0x1200, 0x1300 */
		offset += idx * board->uart_offset + 0xC00;
	} else /* we have only 8 ports on PMC-OCTALPRO */
		return 1;

	return setup_port(priv, port, bar, offset, board->reg_shift);
}