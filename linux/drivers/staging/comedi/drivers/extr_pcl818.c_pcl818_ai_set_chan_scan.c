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
 scalar_t__ PCL818_MUX_REG ; 
 int /*<<< orphan*/  PCL818_MUX_SCAN (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pcl818_ai_set_chan_scan(struct comedi_device *dev,
				    unsigned int first_chan,
				    unsigned int last_chan)
{
	outb(PCL818_MUX_SCAN(first_chan, last_chan),
	     dev->iobase + PCL818_MUX_REG);
}