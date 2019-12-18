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
typedef  int irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTERRUPT_ACK ; 
 int /*<<< orphan*/  INTERRUPT_STATUS ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int ddbreadl (struct ddb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddbwritel (struct ddb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_handle_io (struct ddb*,int) ; 
 int /*<<< orphan*/  irq_handle_msg (struct ddb*,int) ; 

irqreturn_t ddb_irq_handler(int irq, void *dev_id)
{
	struct ddb *dev = (struct ddb *)dev_id;
	u32 s = ddbreadl(dev, INTERRUPT_STATUS);
	int ret = IRQ_HANDLED;

	if (!s)
		return IRQ_NONE;
	do {
		if (s & 0x80000000)
			return IRQ_NONE;
		ddbwritel(dev, s, INTERRUPT_ACK);

		if (s & 0x0000000f)
			irq_handle_msg(dev, s);
		if (s & 0x0fffff00)
			irq_handle_io(dev, s);
	} while ((s = ddbreadl(dev, INTERRUPT_STATUS)));

	return ret;
}