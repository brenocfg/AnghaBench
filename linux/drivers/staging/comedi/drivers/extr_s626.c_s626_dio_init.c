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
typedef  scalar_t__ u16 ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ S626_DIO_BANKS ; 
 int /*<<< orphan*/  S626_LP_MISC1 ; 
 int /*<<< orphan*/  S626_LP_WRCAPSEL (scalar_t__) ; 
 int /*<<< orphan*/  S626_LP_WRDOUT (scalar_t__) ; 
 int /*<<< orphan*/  S626_LP_WREDGSEL (scalar_t__) ; 
 int /*<<< orphan*/  S626_LP_WRINTSEL (scalar_t__) ; 
 int S626_MISC1_NOEDCAP ; 
 int /*<<< orphan*/  s626_debi_write (struct comedi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s626_dio_init(struct comedi_device *dev)
{
	u16 group;

	/* Prepare to treat writes to WRCapSel as capture disables. */
	s626_debi_write(dev, S626_LP_MISC1, S626_MISC1_NOEDCAP);

	/* For each group of sixteen channels ... */
	for (group = 0; group < S626_DIO_BANKS; group++) {
		/* Disable all interrupts */
		s626_debi_write(dev, S626_LP_WRINTSEL(group), 0);
		/* Disable all event captures */
		s626_debi_write(dev, S626_LP_WRCAPSEL(group), 0xffff);
		/* Init all DIOs to default edge polarity */
		s626_debi_write(dev, S626_LP_WREDGSEL(group), 0);
		/* Program all outputs to inactive state */
		s626_debi_write(dev, S626_LP_WRDOUT(group), 0);
	}
}