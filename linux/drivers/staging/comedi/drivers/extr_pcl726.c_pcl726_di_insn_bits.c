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
struct pcl726_board {scalar_t__ is_pcl727; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {scalar_t__ iobase; struct pcl726_board* board_ptr; } ;

/* Variables and functions */
 scalar_t__ PCL726_DI_LSB_REG ; 
 scalar_t__ PCL726_DI_MSB_REG ; 
 scalar_t__ PCL727_DI_LSB_REG ; 
 scalar_t__ PCL727_DI_MSB_REG ; 
 int inb (scalar_t__) ; 

__attribute__((used)) static int pcl726_di_insn_bits(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn,
			       unsigned int *data)
{
	const struct pcl726_board *board = dev->board_ptr;
	unsigned int val;

	if (board->is_pcl727) {
		val = inb(dev->iobase + PCL727_DI_LSB_REG);
		val |= (inb(dev->iobase + PCL727_DI_MSB_REG) << 8);
	} else {
		val = inb(dev->iobase + PCL726_DI_LSB_REG);
		val |= (inb(dev->iobase + PCL726_DI_MSB_REG) << 8);
	}

	data[1] = val;

	return insn->n;
}