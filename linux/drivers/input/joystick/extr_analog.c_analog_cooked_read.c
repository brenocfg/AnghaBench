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
typedef  int /*<<< orphan*/  u64 ;
struct gameport {int dummy; } ;
struct analog_port {int loop; unsigned int speed; unsigned char mask; unsigned int* axes; struct gameport* gameport; } ;

/* Variables and functions */
 unsigned int ANALOG_FUZZ_BITS ; 
 int ANALOG_LOOP_TIME ; 
 unsigned int ANALOG_MAX_TIME ; 
 unsigned int delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char gameport_read (struct gameport*) ; 
 int /*<<< orphan*/  gameport_trigger (struct gameport*) ; 
 int /*<<< orphan*/  get_time () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int analog_cooked_read(struct analog_port *port)
{
	struct gameport *gameport = port->gameport;
	u64 time[4], start, loop, now;
	unsigned int loopout, timeout;
	unsigned char data[4], this, last;
	unsigned long flags;
	int i, j;

	loopout = (ANALOG_LOOP_TIME * port->loop) / 1000;
	timeout = ANALOG_MAX_TIME * port->speed;

	local_irq_save(flags);
	gameport_trigger(gameport);
	now = get_time();
	local_irq_restore(flags);

	start = now;
	this = port->mask;
	i = 0;

	do {
		loop = now;
		last = this;

		local_irq_disable();
		this = gameport_read(gameport) & port->mask;
		now = get_time();
		local_irq_restore(flags);

		if ((last ^ this) && (delta(loop, now) < loopout)) {
			data[i] = last ^ this;
			time[i] = now;
			i++;
		}

	} while (this && (i < 4) && (delta(start, now) < timeout));

	this <<= 4;

	for (--i; i >= 0; i--) {
		this |= data[i];
		for (j = 0; j < 4; j++)
			if (data[i] & (1 << j))
				port->axes[j] = (delta(start, time[i]) << ANALOG_FUZZ_BITS) / port->loop;
	}

	return -(this != port->mask);
}