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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; } ;
struct comedi_cmd {int chanlist_len; int /*<<< orphan*/ * chanlist; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int usbduxfast_ai_check_chanlist(struct comedi_device *dev,
					struct comedi_subdevice *s,
					struct comedi_cmd *cmd)
{
	unsigned int gain0 = CR_RANGE(cmd->chanlist[0]);
	int i;

	if (cmd->chanlist_len > 3 && cmd->chanlist_len != 16) {
		dev_err(dev->class_dev, "unsupported combination of channels\n");
		return -EINVAL;
	}

	for (i = 0; i < cmd->chanlist_len; ++i) {
		unsigned int chan = CR_CHAN(cmd->chanlist[i]);
		unsigned int gain = CR_RANGE(cmd->chanlist[i]);

		if (chan != i) {
			dev_err(dev->class_dev,
				"channels are not consecutive\n");
			return -EINVAL;
		}
		if (gain != gain0 && cmd->chanlist_len > 3) {
			dev_err(dev->class_dev,
				"gain must be the same for all channels\n");
			return -EINVAL;
		}
	}
	return 0;
}