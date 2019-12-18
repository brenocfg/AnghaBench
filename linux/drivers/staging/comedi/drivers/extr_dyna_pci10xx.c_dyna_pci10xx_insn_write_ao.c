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
struct dyna_pci10xx_private {int /*<<< orphan*/  mutex; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int /*<<< orphan*/  iobase; struct dyna_pci10xx_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outw_p (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int dyna_pci10xx_insn_write_ao(struct comedi_device *dev,
				      struct comedi_subdevice *s,
				      struct comedi_insn *insn,
				      unsigned int *data)
{
	struct dyna_pci10xx_private *devpriv = dev->private;
	int n;

	mutex_lock(&devpriv->mutex);
	for (n = 0; n < insn->n; n++) {
		smp_mb();
		/* trigger conversion and write data */
		outw_p(data[n], dev->iobase);
		usleep_range(10, 20);
	}
	mutex_unlock(&devpriv->mutex);
	return n;
}