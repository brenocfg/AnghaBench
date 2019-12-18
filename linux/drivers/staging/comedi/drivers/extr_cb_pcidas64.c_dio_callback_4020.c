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
struct pcidas64_private {scalar_t__ main_iobase; } ;
struct comedi_device {struct pcidas64_private* private; } ;

/* Variables and functions */
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int dio_callback_4020(struct comedi_device *dev,
			     int dir, int port, int data, unsigned long iobase)
{
	struct pcidas64_private *devpriv = dev->private;

	if (dir) {
		writew(data, devpriv->main_iobase + iobase + 2 * port);
		return 0;
	}
	return readw(devpriv->main_iobase + iobase + 2 * port);
}