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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int ME4000_AI_CTRL_IMMEDIATE_STOP ; 
 scalar_t__ ME4000_AI_CTRL_REG ; 
 unsigned int ME4000_AI_CTRL_STOP ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static void me4000_ai_reset(struct comedi_device *dev)
{
	unsigned int ctrl;

	/* Stop any running conversion */
	ctrl = inl(dev->iobase + ME4000_AI_CTRL_REG);
	ctrl |= ME4000_AI_CTRL_STOP | ME4000_AI_CTRL_IMMEDIATE_STOP;
	outl(ctrl, dev->iobase + ME4000_AI_CTRL_REG);

	/* Clear the control register */
	outl(0x0, dev->iobase + ME4000_AI_CTRL_REG);
}