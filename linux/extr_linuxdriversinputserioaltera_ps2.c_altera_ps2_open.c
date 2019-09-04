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
struct serio {struct ps2if* port_data; } ;
struct ps2if {scalar_t__ base; } ;

/* Variables and functions */
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int altera_ps2_open(struct serio *io)
{
	struct ps2if *ps2if = io->port_data;

	/* clear fifo */
	while (readl(ps2if->base) & 0xffff0000)
		/* empty */;

	writel(1, ps2if->base + 4); /* enable rx irq */
	return 0;
}