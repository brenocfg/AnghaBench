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
typedef  int /*<<< orphan*/  u32 ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INSN_CONFIG_ARM 130 
#define  INSN_CONFIG_DISARM 129 
#define  INSN_CONFIG_RESET 128 
 int /*<<< orphan*/  START_COUNTER ; 
 int /*<<< orphan*/  STOP_COUNTER ; 
 int /*<<< orphan*/  WRITE_COUNTER ; 
 int ni6501_counter_command (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ni6501_cnt_insn_config(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn,
				  unsigned int *data)
{
	int ret;
	u32 val = 0;

	switch (data[0]) {
	case INSN_CONFIG_ARM:
		ret = ni6501_counter_command(dev, START_COUNTER, NULL);
		break;
	case INSN_CONFIG_DISARM:
		ret = ni6501_counter_command(dev, STOP_COUNTER, NULL);
		break;
	case INSN_CONFIG_RESET:
		ret = ni6501_counter_command(dev, STOP_COUNTER, NULL);
		if (ret)
			break;
		ret = ni6501_counter_command(dev, WRITE_COUNTER, &val);
		break;
	default:
		return -EINVAL;
	}

	return ret ? ret : insn->n;
}