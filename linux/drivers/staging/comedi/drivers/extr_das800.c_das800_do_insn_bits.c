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
struct das800_private {int do_bits; } ;
struct comedi_subdevice {int state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; struct das800_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL1 ; 
 int CONTROL1_INTE ; 
 scalar_t__ comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 int /*<<< orphan*/  das800_ind_write (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int das800_do_insn_bits(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn,
			       unsigned int *data)
{
	struct das800_private *devpriv = dev->private;
	unsigned long irq_flags;

	if (comedi_dio_update_state(s, data)) {
		devpriv->do_bits = s->state << 4;

		spin_lock_irqsave(&dev->spinlock, irq_flags);
		das800_ind_write(dev, CONTROL1_INTE | devpriv->do_bits,
				 CONTROL1);
		spin_unlock_irqrestore(&dev->spinlock, irq_flags);
	}

	data[1] = s->state;

	return insn->n;
}