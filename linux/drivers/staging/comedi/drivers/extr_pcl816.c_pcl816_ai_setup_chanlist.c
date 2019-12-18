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
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_RANGE (unsigned int) ; 
 int /*<<< orphan*/  pcl816_ai_set_chan_range (struct comedi_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pcl816_ai_set_chan_scan (struct comedi_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void pcl816_ai_setup_chanlist(struct comedi_device *dev,
				     unsigned int *chanlist,
				     unsigned int seglen)
{
	unsigned int first_chan = CR_CHAN(chanlist[0]);
	unsigned int last_chan;
	unsigned int range;
	unsigned int i;

	/* store range list to card */
	for (i = 0; i < seglen; i++) {
		last_chan = CR_CHAN(chanlist[i]);
		range = CR_RANGE(chanlist[i]);

		pcl816_ai_set_chan_range(dev, last_chan, range);
	}

	udelay(1);

	pcl816_ai_set_chan_scan(dev, first_chan, last_chan);
}