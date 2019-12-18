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
 int /*<<< orphan*/  PCMMIO_PAGE_ENAB ; 
 int /*<<< orphan*/  PCMMIO_PAGE_INT_ID ; 
 int /*<<< orphan*/  PCMMIO_PAGE_POL ; 
 int /*<<< orphan*/  pcmmio_dio_write (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pcmmio_reset(struct comedi_device *dev)
{
	/* Clear all the DIO port bits */
	pcmmio_dio_write(dev, 0, 0, 0);
	pcmmio_dio_write(dev, 0, 0, 3);

	/* Clear all the paged registers */
	pcmmio_dio_write(dev, 0, PCMMIO_PAGE_POL, 0);
	pcmmio_dio_write(dev, 0, PCMMIO_PAGE_ENAB, 0);
	pcmmio_dio_write(dev, 0, PCMMIO_PAGE_INT_ID, 0);
}