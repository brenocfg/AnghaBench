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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int COMEDI_OUTPUT ; 
 int /*<<< orphan*/  NISTC_IO_BIDIR_PIN_REG ; 
 int NI_PFI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_set_bits (struct comedi_device*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static void ni_set_pfi_direction(struct comedi_device *dev, int chan,
				 unsigned int direction)
{
	if (chan >= NI_PFI(0)) {
		/* allow new and old names of pfi channels to work. */
		chan -= NI_PFI(0);
	}
	direction = (direction == COMEDI_OUTPUT) ? 1u : 0u;
	ni_set_bits(dev, NISTC_IO_BIDIR_PIN_REG, 1 << chan, direction);
}