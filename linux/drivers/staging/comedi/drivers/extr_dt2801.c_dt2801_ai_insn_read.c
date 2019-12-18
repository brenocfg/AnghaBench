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
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CR_RANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DT_C_READ_ADIM ; 
 int dt2801_error (struct comedi_device*,int) ; 
 int dt2801_readdata2 (struct comedi_device*,int*) ; 
 int /*<<< orphan*/  dt2801_writecmd (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt2801_writedata (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dt2801_ai_insn_read(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn, unsigned int *data)
{
	int d;
	int stat;
	int i;

	for (i = 0; i < insn->n; i++) {
		dt2801_writecmd(dev, DT_C_READ_ADIM);
		dt2801_writedata(dev, CR_RANGE(insn->chanspec));
		dt2801_writedata(dev, CR_CHAN(insn->chanspec));
		stat = dt2801_readdata2(dev, &d);

		if (stat != 0)
			return dt2801_error(dev, stat);

		data[i] = d;
	}

	return i;
}