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
struct serial_state {int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  receive_chars (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rs_interrupt_single(int irq, void *dev_id)
{
	struct serial_state *info = dev_id;

	receive_chars(&info->port);

	return IRQ_HANDLED;
}