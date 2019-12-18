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
struct ipoctal {int /*<<< orphan*/ * channel; scalar_t__ int_space; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ ACK_INT_REQ0 ; 
 scalar_t__ ACK_INT_REQ1 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int NR_CHANNELS ; 
 int /*<<< orphan*/  ipoctal_irq_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 

__attribute__((used)) static irqreturn_t ipoctal_irq_handler(void *arg)
{
	unsigned int i;
	struct ipoctal *ipoctal = (struct ipoctal *) arg;

	/* Clear the IPack device interrupt */
	readw(ipoctal->int_space + ACK_INT_REQ0);
	readw(ipoctal->int_space + ACK_INT_REQ1);

	/* Check all channels */
	for (i = 0; i < NR_CHANNELS; i++)
		ipoctal_irq_channel(&ipoctal->channel[i]);

	return IRQ_HANDLED;
}