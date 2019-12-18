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
typedef  unsigned long long u64 ;
struct ni_660x_private {unsigned long long io_dir; int /*<<< orphan*/ * io_cfg; } ;
struct comedi_device {struct ni_660x_private* private; } ;

/* Variables and functions */
 unsigned int COMEDI_OUTPUT ; 
 unsigned int NI_PFI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_660x_select_pfi_output (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_660x_set_pfi_direction(struct comedi_device *dev,
				      unsigned int chan,
				      unsigned int direction)
{
	struct ni_660x_private *devpriv = dev->private;
	u64 bit;

	if (chan >= NI_PFI(0))
		/* allow new and old names of pfi channels to work. */
		chan -= NI_PFI(0);

	bit = 1ULL << chan;

	if (direction == COMEDI_OUTPUT) {
		devpriv->io_dir |= bit;
		/* reset the output to currently assigned output value */
		ni_660x_select_pfi_output(dev, chan, devpriv->io_cfg[chan]);
	} else {
		devpriv->io_dir &= ~bit;
		/* set pin to high-z; do not change currently assigned route */
		ni_660x_select_pfi_output(dev, chan, 0);
	}
}