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
struct comedi_subdevice {int /*<<< orphan*/  state; scalar_t__ private; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S626_LP_RDDIN (unsigned long) ; 
 int /*<<< orphan*/  S626_LP_WRDOUT (unsigned long) ; 
 scalar_t__ comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 unsigned int s626_debi_read (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_debi_write (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s626_dio_insn_bits(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned long group = (unsigned long)s->private;

	if (comedi_dio_update_state(s, data))
		s626_debi_write(dev, S626_LP_WRDOUT(group), s->state);

	data[1] = s626_debi_read(dev, S626_LP_RDDIN(group));

	return insn->n;
}