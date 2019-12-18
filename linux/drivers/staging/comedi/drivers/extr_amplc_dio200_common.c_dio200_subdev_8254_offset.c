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
struct dio200_board {scalar_t__ is_pcie; } ;
struct comedi_subdevice {struct comedi_8254* private; } ;
struct comedi_device {unsigned int mmio; unsigned int iobase; struct dio200_board* board_ptr; } ;
struct comedi_8254 {unsigned int mmio; unsigned int iobase; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int dio200_subdev_8254_offset(struct comedi_device *dev,
					      struct comedi_subdevice *s)
{
	const struct dio200_board *board = dev->board_ptr;
	struct comedi_8254 *i8254 = s->private;
	unsigned int offset;

	/* get the offset that was passed to comedi_8254_*_init() */
	if (dev->mmio)
		offset = i8254->mmio - dev->mmio;
	else
		offset = i8254->iobase - dev->iobase;

	/* remove the shift that was added for PCIe boards */
	if (board->is_pcie)
		offset >>= 3;

	/* this offset now works for the dio200_{read,write} helpers */
	return offset;
}