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
typedef  unsigned int uint8_t ;
struct adp5520_chip {int /*<<< orphan*/  client; int /*<<< orphan*/  notifier_list; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int ADP5520_CMPR_INT ; 
 unsigned int ADP5520_GPI_INT ; 
 unsigned int ADP5520_KP_INT ; 
 unsigned int ADP5520_KR_INT ; 
 int /*<<< orphan*/  ADP5520_MODE_STATUS ; 
 unsigned int ADP5520_OVP_INT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  __adp5520_ack_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int __adp5520_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t adp5520_irq_thread(int irq, void *data)
{
	struct adp5520_chip *chip = data;
	unsigned int events;
	uint8_t reg_val;
	int ret;

	ret = __adp5520_read(chip->client, ADP5520_MODE_STATUS, &reg_val);
	if (ret)
		goto out;

	events =  reg_val & (ADP5520_OVP_INT | ADP5520_CMPR_INT |
		ADP5520_GPI_INT | ADP5520_KR_INT | ADP5520_KP_INT);

	blocking_notifier_call_chain(&chip->notifier_list, events, NULL);
	/* ACK, Sticky bits are W1C */
	__adp5520_ack_bits(chip->client, ADP5520_MODE_STATUS, events);

out:
	return IRQ_HANDLED;
}