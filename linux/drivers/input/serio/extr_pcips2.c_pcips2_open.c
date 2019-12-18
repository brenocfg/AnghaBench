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
struct serio {struct pcips2_data* port_data; } ;
struct pcips2_data {int /*<<< orphan*/  base; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int PS2_CTRL_ENABLE ; 
 int PS2_CTRL_RXIRQ ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcips2_flush_input (struct pcips2_data*) ; 
 int /*<<< orphan*/  pcips2_interrupt ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct pcips2_data*) ; 

__attribute__((used)) static int pcips2_open(struct serio *io)
{
	struct pcips2_data *ps2if = io->port_data;
	int ret, val = 0;

	outb(PS2_CTRL_ENABLE, ps2if->base);
	pcips2_flush_input(ps2if);

	ret = request_irq(ps2if->dev->irq, pcips2_interrupt, IRQF_SHARED,
			  "pcips2", ps2if);
	if (ret == 0)
		val = PS2_CTRL_ENABLE | PS2_CTRL_RXIRQ;

	outb(val, ps2if->base);

	return ret;
}