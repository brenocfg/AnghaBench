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
struct gameport {int dummy; } ;

/* Variables and functions */
 int SW_END ; 
 int SW_KICK ; 
 int SW_START ; 
 int SW_STROBE ; 
 int SW_TIMEOUT ; 
 unsigned char gameport_read (struct gameport*) ; 
 int gameport_time (struct gameport*,int) ; 
 int /*<<< orphan*/  gameport_trigger (struct gameport*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int sw_read_packet(struct gameport *gameport, unsigned char *buf, int length, int id)
{
	unsigned long flags;
	int timeout, bitout, sched, i, kick, start, strobe;
	unsigned char pending, u, v;

	i = -id;						/* Don't care about data, only want ID */
	timeout = id ? gameport_time(gameport, SW_TIMEOUT * 1000) : 0; /* Set up global timeout for ID packet */
	kick = id ? gameport_time(gameport, SW_KICK) : 0;	/* Set up kick timeout for ID packet */
	start = gameport_time(gameport, SW_START);
	strobe = gameport_time(gameport, SW_STROBE);
	bitout = start;
	pending = 0;
	sched = 0;

        local_irq_save(flags);					/* Quiet, please */

	gameport_trigger(gameport);				/* Trigger */
	v = gameport_read(gameport);

	do {
		bitout--;
		u = v;
		v = gameport_read(gameport);
	} while (!(~v & u & 0x10) && (bitout > 0));		/* Wait for first falling edge on clock */

	if (bitout > 0)
		bitout = strobe;				/* Extend time if not timed out */

	while ((timeout > 0 || bitout > 0) && (i < length)) {

		timeout--;
		bitout--;					/* Decrement timers */
		sched--;

		u = v;
		v = gameport_read(gameport);

		if ((~u & v & 0x10) && (bitout > 0)) {		/* Rising edge on clock - data bit */
			if (i >= 0)				/* Want this data */
				buf[i] = v >> 5;		/* Store it */
			i++;					/* Advance index */
			bitout = strobe;			/* Extend timeout for next bit */
		}

		if (kick && (~v & u & 0x01)) {			/* Falling edge on axis 0 */
			sched = kick;				/* Schedule second trigger */
			kick = 0;				/* Don't schedule next time on falling edge */
			pending = 1;				/* Mark schedule */
		}

		if (pending && sched < 0 && (i > -SW_END)) {	/* Second trigger time */
			gameport_trigger(gameport);		/* Trigger */
			bitout = start;				/* Long bit timeout */
			pending = 0;				/* Unmark schedule */
			timeout = 0;				/* Switch from global to bit timeouts */
		}
	}

	local_irq_restore(flags);					/* Done - relax */

#ifdef SW_DEBUG_DATA
	{
		int j;
		printk(KERN_DEBUG "sidewinder.c: Read %d triplets. [", i);
		for (j = 0; j < i; j++) printk("%d", buf[j]);
		printk("]\n");
	}
#endif

	return i;
}