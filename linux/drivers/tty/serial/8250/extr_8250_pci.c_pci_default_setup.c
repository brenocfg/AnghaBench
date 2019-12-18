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
struct serial_private {int /*<<< orphan*/  dev; } ;
struct pciserial_board {unsigned int first_offset; int flags; int uart_offset; int reg_shift; } ;

/* Variables and functions */
 int FL_BASE_BARS ; 
 unsigned int FL_GET_BASE (int) ; 
 int FL_REGION_SZ_CAP ; 
 int pci_resource_len (int /*<<< orphan*/ ,unsigned int) ; 
 int setup_port (struct serial_private*,struct uart_8250_port*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int pci_default_setup(struct serial_private *priv,
		  const struct pciserial_board *board,
		  struct uart_8250_port *port, int idx)
{
	unsigned int bar, offset = board->first_offset, maxnr;

	bar = FL_GET_BASE(board->flags);
	if (board->flags & FL_BASE_BARS)
		bar += idx;
	else
		offset += idx * board->uart_offset;

	maxnr = (pci_resource_len(priv->dev, bar) - board->first_offset) >>
		(board->reg_shift + 3);

	if (board->flags & FL_REGION_SZ_CAP && idx >= maxnr)
		return 1;

	return setup_port(priv, port, bar, offset, board->reg_shift);
}