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
 int /*<<< orphan*/  S626_LP_MISC1 ; 
 int /*<<< orphan*/  S626_LP_RDCAPSEL (unsigned int) ; 
 int /*<<< orphan*/  S626_LP_RDEDGSEL (unsigned int) ; 
 int /*<<< orphan*/  S626_LP_RDINTSEL (unsigned int) ; 
 int /*<<< orphan*/  S626_LP_WRCAPSEL (unsigned int) ; 
 int /*<<< orphan*/  S626_LP_WREDGSEL (unsigned int) ; 
 int /*<<< orphan*/  S626_LP_WRINTSEL (unsigned int) ; 
 unsigned int S626_MISC1_EDCAP ; 
 unsigned int s626_debi_read (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_debi_write (struct comedi_device*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int s626_dio_set_irq(struct comedi_device *dev, unsigned int chan)
{
	unsigned int group = chan / 16;
	unsigned int mask = 1 << (chan - (16 * group));
	unsigned int status;

	/* set channel to capture positive edge */
	status = s626_debi_read(dev, S626_LP_RDEDGSEL(group));
	s626_debi_write(dev, S626_LP_WREDGSEL(group), mask | status);

	/* enable interrupt on selected channel */
	status = s626_debi_read(dev, S626_LP_RDINTSEL(group));
	s626_debi_write(dev, S626_LP_WRINTSEL(group), mask | status);

	/* enable edge capture write command */
	s626_debi_write(dev, S626_LP_MISC1, S626_MISC1_EDCAP);

	/* enable edge capture on selected channel */
	status = s626_debi_read(dev, S626_LP_RDCAPSEL(group));
	s626_debi_write(dev, S626_LP_WRCAPSEL(group), mask | status);

	return 0;
}