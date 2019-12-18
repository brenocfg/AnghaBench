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
struct pci1710_private {int saved_seglen; } ;
struct comedi_subdevice {unsigned int n_chan; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct pci1710_private* private; } ;
struct comedi_cmd {unsigned int* chanlist; int chanlist_len; } ;

/* Variables and functions */
 unsigned int AREF_DIFF ; 
 unsigned int CR_AREF (unsigned int) ; 
 unsigned int CR_CHAN (unsigned int) ; 
 int /*<<< orphan*/  CR_RANGE (unsigned int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int pci1710_ai_check_chanlist(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_cmd *cmd)
{
	struct pci1710_private *devpriv = dev->private;
	unsigned int chan0 = CR_CHAN(cmd->chanlist[0]);
	unsigned int last_aref = CR_AREF(cmd->chanlist[0]);
	unsigned int next_chan = (chan0 + 1) % s->n_chan;
	unsigned int chansegment[32];
	unsigned int seglen;
	int i;

	if (cmd->chanlist_len == 1) {
		devpriv->saved_seglen = cmd->chanlist_len;
		return 0;
	}

	/* first channel is always ok */
	chansegment[0] = cmd->chanlist[0];

	for (i = 1; i < cmd->chanlist_len; i++) {
		unsigned int chan = CR_CHAN(cmd->chanlist[i]);
		unsigned int aref = CR_AREF(cmd->chanlist[i]);

		if (cmd->chanlist[0] == cmd->chanlist[i])
			break;	/*  we detected a loop, stop */

		if (aref == AREF_DIFF && (chan & 1)) {
			dev_err(dev->class_dev,
				"Odd channel cannot be differential input!\n");
			return -EINVAL;
		}

		if (last_aref == AREF_DIFF)
			next_chan = (next_chan + 1) % s->n_chan;
		if (chan != next_chan) {
			dev_err(dev->class_dev,
				"channel list must be continuous! chanlist[%i]=%d but must be %d or %d!\n",
				i, chan, next_chan, chan0);
			return -EINVAL;
		}

		/* next correct channel in list */
		chansegment[i] = cmd->chanlist[i];
		last_aref = aref;
	}
	seglen = i;

	for (i = 0; i < cmd->chanlist_len; i++) {
		if (cmd->chanlist[i] != chansegment[i % seglen]) {
			dev_err(dev->class_dev,
				"bad channel, reference or range number! chanlist[%i]=%d,%d,%d and not %d,%d,%d!\n",
				i, CR_CHAN(chansegment[i]),
				CR_RANGE(chansegment[i]),
				CR_AREF(chansegment[i]),
				CR_CHAN(cmd->chanlist[i % seglen]),
				CR_RANGE(cmd->chanlist[i % seglen]),
				CR_AREF(chansegment[i % seglen]));
			return -EINVAL;
		}
	}
	devpriv->saved_seglen = seglen;

	return 0;
}