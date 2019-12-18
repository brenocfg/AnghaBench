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
struct comedi_device {struct cb_pcimdas_private* private; } ;
struct cb_pcimdas_private {scalar_t__ BADR3; } ;

/* Variables and functions */
 scalar_t__ PCIMDAS_STATUS_REG ; 
 unsigned int PCIMDAS_STATUS_UB ; 
 unsigned int inb (scalar_t__) ; 

__attribute__((used)) static bool cb_pcimdas_is_ai_uni(struct comedi_device *dev)
{
	struct cb_pcimdas_private *devpriv = dev->private;
	unsigned int status;

	/*
	 * The Analog Input range polarity is set with the
	 * Analog Input Polarity Switch on the board. The
	 * inputs can be set to Unipolar or Bipolar ranges.
	 */
	status = inb(devpriv->BADR3 + PCIMDAS_STATUS_REG);
	return status & PCIMDAS_STATUS_UB;
}