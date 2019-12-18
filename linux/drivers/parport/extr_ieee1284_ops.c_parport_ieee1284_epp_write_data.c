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
struct parport {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* data_forward ) (struct parport*) ;} ;

/* Variables and functions */
 int PARPORT_CONTROL_AUTOFD ; 
 int PARPORT_CONTROL_INIT ; 
 int PARPORT_CONTROL_SELECT ; 
 int PARPORT_CONTROL_STROBE ; 
 int /*<<< orphan*/  PARPORT_STATUS_BUSY ; 
 int /*<<< orphan*/  parport_frob_control (struct parport*,int,int) ; 
 scalar_t__ parport_poll_peripheral (struct parport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parport_write_data (struct parport*,unsigned char) ; 
 int /*<<< orphan*/  stub1 (struct parport*) ; 

size_t parport_ieee1284_epp_write_data (struct parport *port,
					const void *buffer, size_t len,
					int flags)
{
	unsigned char *bp = (unsigned char *) buffer;
	size_t ret = 0;

	/* set EPP idle state (just to make sure) with strobe low */
	parport_frob_control (port,
			      PARPORT_CONTROL_STROBE |
			      PARPORT_CONTROL_AUTOFD |
			      PARPORT_CONTROL_SELECT |
			      PARPORT_CONTROL_INIT,
			      PARPORT_CONTROL_STROBE |
			      PARPORT_CONTROL_INIT);
	port->ops->data_forward (port);
	for (; len > 0; len--, bp++) {
		/* Event 62: Write data and set autofd low */
		parport_write_data (port, *bp);
		parport_frob_control (port, PARPORT_CONTROL_AUTOFD,
				      PARPORT_CONTROL_AUTOFD);

		/* Event 58: wait for busy (nWait) to go high */
		if (parport_poll_peripheral (port, PARPORT_STATUS_BUSY, 0, 10))
			break;

		/* Event 63: set nAutoFd (nDStrb) high */
		parport_frob_control (port, PARPORT_CONTROL_AUTOFD, 0);

		/* Event 60: wait for busy (nWait) to go low */
		if (parport_poll_peripheral (port, PARPORT_STATUS_BUSY,
					     PARPORT_STATUS_BUSY, 5))
			break;

		ret++;
	}

	/* Event 61: set strobe (nWrite) high */
	parport_frob_control (port, PARPORT_CONTROL_STROBE, 0);

	return ret;
}