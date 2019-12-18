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
struct comedi_insn {int n; unsigned int subdev; int /*<<< orphan*/  chanspec; int /*<<< orphan*/  insn; } ;
struct comedi_device {int dummy; } ;
typedef  int /*<<< orphan*/  insn ;

/* Variables and functions */
 int /*<<< orphan*/  CR_PACK (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_CONFIG ; 
 unsigned int INSN_CONFIG_DIO_QUERY ; 
 int comedi_do_insn (struct comedi_device*,struct comedi_insn*,unsigned int*) ; 
 int /*<<< orphan*/  memset (struct comedi_insn*,int /*<<< orphan*/ ,int) ; 

int comedi_dio_get_config(struct comedi_device *dev, unsigned int subdev,
			  unsigned int chan, unsigned int *io)
{
	struct comedi_insn insn;
	unsigned int data[2];
	int ret;

	memset(&insn, 0, sizeof(insn));
	insn.insn = INSN_CONFIG;
	insn.n = 2;
	insn.subdev = subdev;
	insn.chanspec = CR_PACK(chan, 0, 0);
	data[0] = INSN_CONFIG_DIO_QUERY;
	data[1] = 0;
	ret = comedi_do_insn(dev, &insn, data);
	if (ret >= 0)
		*io = data[1];
	return ret;
}