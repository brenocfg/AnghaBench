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
struct egpio_info {int ack_register; int bus_shift; int /*<<< orphan*/  ack_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  egpio_writew (int /*<<< orphan*/ ,struct egpio_info*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ack_irqs(struct egpio_info *ei)
{
	egpio_writew(ei->ack_write, ei, ei->ack_register);
	pr_debug("EGPIO ack - write %x to base+%x\n",
			ei->ack_write, ei->ack_register << ei->bus_shift);
}