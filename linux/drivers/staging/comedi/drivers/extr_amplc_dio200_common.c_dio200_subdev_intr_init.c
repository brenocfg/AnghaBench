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
struct dio200_subdev_intr {unsigned int ofs; unsigned int valid_isns; int /*<<< orphan*/  spinlock; } ;
struct dio200_board {scalar_t__ has_int_sce; } ;
struct comedi_subdevice {int subdev_flags; int n_chan; int len_chanlist; int maxdata; int /*<<< orphan*/  cancel; int /*<<< orphan*/  do_cmd; int /*<<< orphan*/  do_cmdtest; int /*<<< orphan*/  insn_bits; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  type; } ;
struct comedi_device {struct dio200_board* board_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_DI ; 
 void* DIO200_MAX_ISNS ; 
 int ENOMEM ; 
 int SDF_CMD_READ ; 
 int SDF_PACKED ; 
 int SDF_READABLE ; 
 struct dio200_subdev_intr* comedi_alloc_spriv (struct comedi_subdevice*,int) ; 
 int /*<<< orphan*/  dio200_subdev_intr_cancel ; 
 int /*<<< orphan*/  dio200_subdev_intr_cmd ; 
 int /*<<< orphan*/  dio200_subdev_intr_cmdtest ; 
 int /*<<< orphan*/  dio200_subdev_intr_insn_bits ; 
 int /*<<< orphan*/  dio200_write8 (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_digital ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dio200_subdev_intr_init(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   unsigned int offset,
				   unsigned int valid_isns)
{
	const struct dio200_board *board = dev->board_ptr;
	struct dio200_subdev_intr *subpriv;

	subpriv = comedi_alloc_spriv(s, sizeof(*subpriv));
	if (!subpriv)
		return -ENOMEM;

	subpriv->ofs = offset;
	subpriv->valid_isns = valid_isns;
	spin_lock_init(&subpriv->spinlock);

	if (board->has_int_sce)
		/* Disable interrupt sources. */
		dio200_write8(dev, subpriv->ofs, 0);

	s->type = COMEDI_SUBD_DI;
	s->subdev_flags = SDF_READABLE | SDF_CMD_READ | SDF_PACKED;
	if (board->has_int_sce) {
		s->n_chan = DIO200_MAX_ISNS;
		s->len_chanlist = DIO200_MAX_ISNS;
	} else {
		/* No interrupt source register.  Support single channel. */
		s->n_chan = 1;
		s->len_chanlist = 1;
	}
	s->range_table = &range_digital;
	s->maxdata = 1;
	s->insn_bits = dio200_subdev_intr_insn_bits;
	s->do_cmdtest = dio200_subdev_intr_cmdtest;
	s->do_cmd = dio200_subdev_intr_cmd;
	s->cancel = dio200_subdev_intr_cancel;

	return 0;
}