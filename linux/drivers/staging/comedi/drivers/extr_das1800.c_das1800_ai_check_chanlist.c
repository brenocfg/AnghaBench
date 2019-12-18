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
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int comedi_range_is_unipolar (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int das1800_ai_check_chanlist(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_cmd *cmd)
{
	unsigned int range = CR_RANGE(cmd->chanlist[0]);
	bool unipolar0 = comedi_range_is_unipolar(s, range);
	int i;

	for (i = 1; i < cmd->chanlist_len; i++) {
		range = CR_RANGE(cmd->chanlist[i]);

		if (unipolar0 != comedi_range_is_unipolar(s, range)) {
			dev_dbg(dev->class_dev,
				"unipolar and bipolar ranges cannot be mixed in the chanlist\n");
			return -EINVAL;
		}
	}

	return 0;
}