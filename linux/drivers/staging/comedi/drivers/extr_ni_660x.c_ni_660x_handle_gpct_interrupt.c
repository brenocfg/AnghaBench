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
struct ni_gpct {int dummy; } ;
struct comedi_subdevice {struct ni_gpct* private; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_handle_events (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  ni_tio_handle_interrupt (struct ni_gpct*,struct comedi_subdevice*) ; 

__attribute__((used)) static void ni_660x_handle_gpct_interrupt(struct comedi_device *dev,
					  struct comedi_subdevice *s)
{
	struct ni_gpct *counter = s->private;

	ni_tio_handle_interrupt(counter, s);
	comedi_handle_events(dev, s);
}