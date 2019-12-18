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
struct pci230_private {scalar_t__ ao_bipolar; } ;
struct pci230_board {int ao_bits; } ;
struct comedi_device {struct pci230_private* private; struct pci230_board* board_ptr; } ;

/* Variables and functions */

__attribute__((used)) static unsigned short pci230_ao_mangle_datum(struct comedi_device *dev,
					     unsigned short datum)
{
	const struct pci230_board *board = dev->board_ptr;
	struct pci230_private *devpriv = dev->private;

	/*
	 * PCI230 is 12 bit - stored in upper bits of 16 bit register (lower
	 * four bits reserved for expansion).  PCI230+ is also 12 bit AO.
	 */
	datum <<= (16 - board->ao_bits);
	/*
	 * If a bipolar range was specified, mangle it
	 * (straight binary->twos complement).
	 */
	if (devpriv->ao_bipolar)
		datum ^= 0x8000;
	return datum;
}