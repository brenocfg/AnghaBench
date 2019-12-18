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
typedef  int u32 ;
struct ddb {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTERRUPT_ACK ; 
 int /*<<< orphan*/  INTERRUPT_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int ddbreadl (struct ddb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddbwritel (struct ddb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_handle_msg (struct ddb*,int) ; 

irqreturn_t ddb_irq_handler1(int irq, void *dev_id)
{
	struct ddb *dev = (struct ddb *)dev_id;
	u32 mask = 0x8000000f;
	u32 s = mask & ddbreadl(dev, INTERRUPT_STATUS);

	if (!s)
		return IRQ_NONE;
	do {
		if (s & 0x80000000)
			return IRQ_NONE;
		ddbwritel(dev, s, INTERRUPT_ACK);
		irq_handle_msg(dev, s);
	} while ((s = mask & ddbreadl(dev, INTERRUPT_STATUS)));

	return IRQ_HANDLED;
}