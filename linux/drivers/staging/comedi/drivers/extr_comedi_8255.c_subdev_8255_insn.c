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
struct subdev_8255_private {unsigned long regbase; unsigned int (* io ) (struct comedi_device*,int,int /*<<< orphan*/ ,int,unsigned long) ;} ;
struct comedi_subdevice {int state; struct subdev_8255_private* private; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I8255_DATA_A_REG ; 
 int /*<<< orphan*/  I8255_DATA_B_REG ; 
 int /*<<< orphan*/  I8255_DATA_C_REG ; 
 unsigned int comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 unsigned int stub1 (struct comedi_device*,int,int /*<<< orphan*/ ,int,unsigned long) ; 
 unsigned int stub2 (struct comedi_device*,int,int /*<<< orphan*/ ,int,unsigned long) ; 
 unsigned int stub3 (struct comedi_device*,int,int /*<<< orphan*/ ,int,unsigned long) ; 
 unsigned int stub4 (struct comedi_device*,int,int /*<<< orphan*/ ,int,unsigned long) ; 
 int stub5 (struct comedi_device*,int,int /*<<< orphan*/ ,int,unsigned long) ; 
 int stub6 (struct comedi_device*,int,int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static int subdev_8255_insn(struct comedi_device *dev,
			    struct comedi_subdevice *s,
			    struct comedi_insn *insn,
			    unsigned int *data)
{
	struct subdev_8255_private *spriv = s->private;
	unsigned long regbase = spriv->regbase;
	unsigned int mask;
	unsigned int v;

	mask = comedi_dio_update_state(s, data);
	if (mask) {
		if (mask & 0xff)
			spriv->io(dev, 1, I8255_DATA_A_REG,
				  s->state & 0xff, regbase);
		if (mask & 0xff00)
			spriv->io(dev, 1, I8255_DATA_B_REG,
				  (s->state >> 8) & 0xff, regbase);
		if (mask & 0xff0000)
			spriv->io(dev, 1, I8255_DATA_C_REG,
				  (s->state >> 16) & 0xff, regbase);
	}

	v = spriv->io(dev, 0, I8255_DATA_A_REG, 0, regbase);
	v |= (spriv->io(dev, 0, I8255_DATA_B_REG, 0, regbase) << 8);
	v |= (spriv->io(dev, 0, I8255_DATA_C_REG, 0, regbase) << 16);

	data[1] = v;

	return insn->n;
}