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
struct ni_private {unsigned int clock_ns; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
#define  CMDF_ROUND_DOWN 130 
 unsigned int CMDF_ROUND_MASK ; 
#define  CMDF_ROUND_NEAREST 129 
#define  CMDF_ROUND_UP 128 
 int DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 int DIV_ROUND_UP (unsigned int,unsigned int) ; 

__attribute__((used)) static int ni_ns_to_timer(const struct comedi_device *dev,
			  unsigned int nanosec, unsigned int flags)
{
	struct ni_private *devpriv = dev->private;
	int divider;

	switch (flags & CMDF_ROUND_MASK) {
	case CMDF_ROUND_NEAREST:
	default:
		divider = DIV_ROUND_CLOSEST(nanosec, devpriv->clock_ns);
		break;
	case CMDF_ROUND_DOWN:
		divider = (nanosec) / devpriv->clock_ns;
		break;
	case CMDF_ROUND_UP:
		divider = DIV_ROUND_UP(nanosec, devpriv->clock_ns);
		break;
	}
	return divider - 1;
}