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
struct pci230_private {scalar_t__ ai_bipolar; scalar_t__ daqio; } ;
struct pci230_board {int ai_bits; } ;
struct comedi_device {struct pci230_private* private; struct pci230_board* board_ptr; } ;

/* Variables and functions */
 scalar_t__ PCI230_ADCDATA ; 
 unsigned short inw (scalar_t__) ; 

__attribute__((used)) static unsigned short pci230_ai_read(struct comedi_device *dev)
{
	const struct pci230_board *board = dev->board_ptr;
	struct pci230_private *devpriv = dev->private;
	unsigned short data;

	/* Read sample. */
	data = inw(devpriv->daqio + PCI230_ADCDATA);
	/*
	 * PCI230 is 12 bit - stored in upper bits of 16 bit register
	 * (lower four bits reserved for expansion).  PCI230+ is 16 bit AI.
	 *
	 * If a bipolar range was specified, mangle it
	 * (twos complement->straight binary).
	 */
	if (devpriv->ai_bipolar)
		data ^= 0x8000;
	data >>= (16 - board->ai_bits);
	return data;
}