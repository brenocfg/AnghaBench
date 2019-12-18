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
struct vsxxxaa {int dummy; } ;
struct serio {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct vsxxxaa* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  vsxxxaa_parse_buffer (struct vsxxxaa*) ; 
 int /*<<< orphan*/  vsxxxaa_queue_byte (struct vsxxxaa*,unsigned char) ; 

__attribute__((used)) static irqreturn_t vsxxxaa_interrupt(struct serio *serio,
				     unsigned char data, unsigned int flags)
{
	struct vsxxxaa *mouse = serio_get_drvdata(serio);

	vsxxxaa_queue_byte(mouse, data);
	vsxxxaa_parse_buffer(mouse);

	return IRQ_HANDLED;
}