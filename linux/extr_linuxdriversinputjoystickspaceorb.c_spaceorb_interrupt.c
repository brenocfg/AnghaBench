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
struct spaceorb {scalar_t__ idx; unsigned char* data; } ;
struct serio {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SPACEORB_MAX_LENGTH ; 
 struct spaceorb* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  spaceorb_process_packet (struct spaceorb*) ; 

__attribute__((used)) static irqreturn_t spaceorb_interrupt(struct serio *serio,
		unsigned char data, unsigned int flags)
{
	struct spaceorb* spaceorb = serio_get_drvdata(serio);

	if (~data & 0x80) {
		if (spaceorb->idx) spaceorb_process_packet(spaceorb);
		spaceorb->idx = 0;
	}
	if (spaceorb->idx < SPACEORB_MAX_LENGTH)
		spaceorb->data[spaceorb->idx++] = data & 0x7f;
	return IRQ_HANDLED;
}