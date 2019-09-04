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
struct stinger {int idx; unsigned char* data; } ;
struct serio {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int STINGER_MAX_LENGTH ; 
 struct stinger* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  stinger_process_packet (struct stinger*) ; 

__attribute__((used)) static irqreturn_t stinger_interrupt(struct serio *serio,
	unsigned char data, unsigned int flags)
{
	struct stinger *stinger = serio_get_drvdata(serio);

	/* All Stinger packets are 4 bytes */

	if (stinger->idx < STINGER_MAX_LENGTH)
		stinger->data[stinger->idx++] = data;

	if (stinger->idx == 4) {
		stinger_process_packet(stinger);
		stinger->idx = 0;
	}

	return IRQ_HANDLED;
}