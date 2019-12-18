#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ni_gpct {int /*<<< orphan*/  chip_index; TYPE_1__* counter_dev; } ;
struct comedi_device {int dummy; } ;
typedef  enum ni_gpct_register { ____Placeholder_ni_gpct_register } ni_gpct_register ;
struct TYPE_2__ {struct comedi_device* dev; } ;

/* Variables and functions */
 unsigned int ni_660x_read (struct comedi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int ni_660x_gpct_read(struct ni_gpct *counter,
				      enum ni_gpct_register reg)
{
	struct comedi_device *dev = counter->counter_dev->dev;

	return ni_660x_read(dev, counter->chip_index, reg);
}