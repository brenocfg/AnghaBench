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
struct ni_private {int /*<<< orphan*/  clock_and_fout; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 unsigned int NISTC_CLK_FOUT_TO_DIVIDER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_freq_out_insn_read(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn,
				 unsigned int *data)
{
	struct ni_private *devpriv = dev->private;
	unsigned int val = NISTC_CLK_FOUT_TO_DIVIDER(devpriv->clock_and_fout);
	int i;

	for (i = 0; i < insn->n; i++)
		data[i] = val;

	return insn->n;
}