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
struct mf6x4_private {int /*<<< orphan*/  gpioc_reg; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {struct mf6x4_private* private; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned int MF6X4_GPIOC_EOLC ; 
 unsigned int ioread32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mf6x4_ai_eoc(struct comedi_device *dev,
			struct comedi_subdevice *s,
			struct comedi_insn *insn,
			unsigned long context)
{
	struct mf6x4_private *devpriv = dev->private;
	unsigned int status;

	status = ioread32(devpriv->gpioc_reg);
	if (status & MF6X4_GPIOC_EOLC)
		return 0;
	return -EBUSY;
}