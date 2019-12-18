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
 unsigned int AREF_DIFF ; 
 unsigned int CR_AREF (unsigned int) ; 
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_RANGE (unsigned int) ; 
 unsigned int DAQP_SCANLIST_CHANNEL (unsigned int) ; 
 unsigned int DAQP_SCANLIST_DIFFERENTIAL ; 
 unsigned int DAQP_SCANLIST_GAIN (unsigned int) ; 
 scalar_t__ DAQP_SCANLIST_REG ; 
 unsigned int DAQP_SCANLIST_START ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void daqp_ai_set_one_scanlist_entry(struct comedi_device *dev,
					   unsigned int chanspec,
					   int start)
{
	unsigned int chan = CR_CHAN(chanspec);
	unsigned int range = CR_RANGE(chanspec);
	unsigned int aref = CR_AREF(chanspec);
	unsigned int val;

	val = DAQP_SCANLIST_CHANNEL(chan) | DAQP_SCANLIST_GAIN(range);

	if (aref == AREF_DIFF)
		val |= DAQP_SCANLIST_DIFFERENTIAL;

	if (start)
		val |= DAQP_SCANLIST_START;

	outb(val & 0xff, dev->iobase + DAQP_SCANLIST_REG);
	outb((val >> 8) & 0xff, dev->iobase + DAQP_SCANLIST_REG);
}