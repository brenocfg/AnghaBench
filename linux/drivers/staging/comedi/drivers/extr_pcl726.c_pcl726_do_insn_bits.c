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
struct comedi_subdevice {int state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {unsigned long iobase; struct pcl726_board* board_ptr; } ;

/* Variables and functions */
 scalar_t__ PCL726_DO_LSB_REG ; 
 scalar_t__ PCL726_DO_MSB_REG ; 
 scalar_t__ PCL727_DO_LSB_REG ; 
 scalar_t__ PCL727_DO_MSB_REG ; 
 unsigned int comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int pcl726_do_insn_bits(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn,
			       unsigned int *data)
{
	const struct pcl726_board *board = dev->board_ptr;
	unsigned long io = dev->iobase;
	unsigned int mask;

	mask = comedi_dio_update_state(s, data);
	if (mask) {
		if (board->is_pcl727) {
			if (mask & 0x00ff)
				outb(s->state & 0xff, io + PCL727_DO_LSB_REG);
			if (mask & 0xff00)
				outb((s->state >> 8), io + PCL727_DO_MSB_REG);
		} else {
			if (mask & 0x00ff)
				outb(s->state & 0xff, io + PCL726_DO_LSB_REG);
			if (mask & 0xff00)
				outb((s->state >> 8), io + PCL726_DO_MSB_REG);
		}
	}

	data[1] = s->state;

	return insn->n;
}