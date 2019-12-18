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
struct dio200_subdev_intr {unsigned int valid_isns; int /*<<< orphan*/  ofs; } ;
struct dio200_board {scalar_t__ has_int_sce; } ;
struct comedi_subdevice {struct dio200_subdev_intr* private; } ;
struct comedi_insn {int n; } ;
struct comedi_device {struct dio200_board* board_ptr; } ;

/* Variables and functions */
 unsigned int dio200_read8 (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dio200_subdev_intr_insn_bits(struct comedi_device *dev,
					struct comedi_subdevice *s,
					struct comedi_insn *insn,
					unsigned int *data)
{
	const struct dio200_board *board = dev->board_ptr;
	struct dio200_subdev_intr *subpriv = s->private;

	if (board->has_int_sce) {
		/* Just read the interrupt status register.  */
		data[1] = dio200_read8(dev, subpriv->ofs) & subpriv->valid_isns;
	} else {
		/* No interrupt status register. */
		data[0] = 0;
	}

	return insn->n;
}