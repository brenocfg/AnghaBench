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
struct ni_660x_private {unsigned int* io_cfg; } ;
struct comedi_device {struct ni_660x_private* private; } ;

/* Variables and functions */
 scalar_t__ COMEDI_OUTPUT ; 
 int EINVAL ; 
#define  NI_660X_PFI_OUTPUT_COUNTER 129 
#define  NI_660X_PFI_OUTPUT_DIO 128 
 unsigned int NI_PFI (int /*<<< orphan*/ ) ; 
 scalar_t__ ni_660x_get_pfi_direction (struct comedi_device*,unsigned int) ; 
 int /*<<< orphan*/  ni_660x_select_pfi_output (struct comedi_device*,unsigned int,unsigned int) ; 

__attribute__((used)) static int ni_660x_set_pfi_routing(struct comedi_device *dev,
				   unsigned int chan, unsigned int source)
{
	struct ni_660x_private *devpriv = dev->private;

	if (chan >= NI_PFI(0))
		/* allow new and old names of pfi channels to work. */
		chan -= NI_PFI(0);

	switch (source) {
	case NI_660X_PFI_OUTPUT_COUNTER:
		if (chan < 8)
			return -EINVAL;
		break;
	case NI_660X_PFI_OUTPUT_DIO:
		if (chan > 31)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	devpriv->io_cfg[chan] = source;
	if (ni_660x_get_pfi_direction(dev, chan) == COMEDI_OUTPUT)
		ni_660x_select_pfi_output(dev, chan, devpriv->io_cfg[chan]);
	return 0;
}