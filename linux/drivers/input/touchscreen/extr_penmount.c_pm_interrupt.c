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
struct serio {int dummy; } ;
struct pm {unsigned char* data; size_t idx; int /*<<< orphan*/  (* parse_packet ) (struct pm*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct pm* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  stub1 (struct pm*) ; 

__attribute__((used)) static irqreturn_t pm_interrupt(struct serio *serio,
		unsigned char data, unsigned int flags)
{
	struct pm *pm = serio_get_drvdata(serio);

	pm->data[pm->idx] = data;

	pm->parse_packet(pm);

	return IRQ_HANDLED;
}