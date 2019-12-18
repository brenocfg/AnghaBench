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
struct pciserial_board {scalar_t__ num_ports; scalar_t__ base_baud; scalar_t__ uart_offset; scalar_t__ reg_shift; scalar_t__ first_offset; } ;

/* Variables and functions */

__attribute__((used)) static inline int
serial_pci_matches(const struct pciserial_board *board,
		   const struct pciserial_board *guessed)
{
	return
	    board->num_ports == guessed->num_ports &&
	    board->base_baud == guessed->base_baud &&
	    board->uart_offset == guessed->uart_offset &&
	    board->reg_shift == guessed->reg_shift &&
	    board->first_offset == guessed->first_offset;
}