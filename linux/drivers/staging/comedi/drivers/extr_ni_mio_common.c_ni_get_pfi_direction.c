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
struct ni_private {int io_bidirection_pin_reg; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 int COMEDI_INPUT ; 
 int COMEDI_OUTPUT ; 
 int NI_PFI (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_get_pfi_direction(struct comedi_device *dev, int chan)
{
	struct ni_private *devpriv = dev->private;

	if (chan >= NI_PFI(0)) {
		/* allow new and old names of pfi channels to work. */
		chan -= NI_PFI(0);
	}
	return devpriv->io_bidirection_pin_reg & (1 << chan) ?
	       COMEDI_OUTPUT : COMEDI_INPUT;
}