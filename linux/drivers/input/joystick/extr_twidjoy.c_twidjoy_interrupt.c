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
struct twidjoy {scalar_t__ idx; unsigned char* data; } ;
struct serio {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TWIDJOY_MAX_LENGTH ; 
 struct twidjoy* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  twidjoy_process_packet (struct twidjoy*) ; 

__attribute__((used)) static irqreturn_t twidjoy_interrupt(struct serio *serio, unsigned char data, unsigned int flags)
{
	struct twidjoy *twidjoy = serio_get_drvdata(serio);

	/* All Twiddler packets are 5 bytes. The fact that the first byte
	 * has a MSB of 0 and all other bytes have a MSB of 1 can be used
	 * to check and regain sync. */

	if ((data & 0x80) == 0)
		twidjoy->idx = 0;	/* this byte starts a new packet */
	else if (twidjoy->idx == 0)
		return IRQ_HANDLED;	/* wrong MSB -- ignore this byte */

	if (twidjoy->idx < TWIDJOY_MAX_LENGTH)
		twidjoy->data[twidjoy->idx++] = data;

	if (twidjoy->idx == TWIDJOY_MAX_LENGTH) {
		twidjoy_process_packet(twidjoy);
		twidjoy->idx = 0;
	}

	return IRQ_HANDLED;
}