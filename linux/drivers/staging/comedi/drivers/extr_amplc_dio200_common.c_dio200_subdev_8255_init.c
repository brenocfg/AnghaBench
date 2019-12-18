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
struct dio200_subdev_8255 {unsigned int ofs; } ;
struct comedi_subdevice {int subdev_flags; int n_chan; int maxdata; int /*<<< orphan*/  insn_config; int /*<<< orphan*/  insn_bits; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  type; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_DIO ; 
 int ENOMEM ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 struct dio200_subdev_8255* comedi_alloc_spriv (struct comedi_subdevice*,int) ; 
 int /*<<< orphan*/  dio200_subdev_8255_bits ; 
 int /*<<< orphan*/  dio200_subdev_8255_config ; 
 int /*<<< orphan*/  dio200_subdev_8255_set_dir (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  range_digital ; 

__attribute__((used)) static int dio200_subdev_8255_init(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   unsigned int offset)
{
	struct dio200_subdev_8255 *subpriv;

	subpriv = comedi_alloc_spriv(s, sizeof(*subpriv));
	if (!subpriv)
		return -ENOMEM;

	subpriv->ofs = offset;

	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags = SDF_READABLE | SDF_WRITABLE;
	s->n_chan = 24;
	s->range_table = &range_digital;
	s->maxdata = 1;
	s->insn_bits = dio200_subdev_8255_bits;
	s->insn_config = dio200_subdev_8255_config;
	dio200_subdev_8255_set_dir(dev, s);
	return 0;
}