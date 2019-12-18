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
struct parport {int dummy; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ need_resched () ; 
 unsigned char parport_read_status (struct parport*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

int parport_poll_peripheral(struct parport *port,
			    unsigned char mask,
			    unsigned char result,
			    int usec)
{
	/* Zero return code is success, >0 is timeout. */
	int count = usec / 5 + 2;
	int i;
	unsigned char status;
	for (i = 0; i < count; i++) {
		status = parport_read_status (port);
		if ((status & mask) == result)
			return 0;
		if (signal_pending (current))
			return -EINTR;
		if (need_resched())
			break;
		if (i >= 2)
			udelay (5);
	}

	return 1;
}