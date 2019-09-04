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
struct rc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  send_pulse (unsigned int) ; 
 int /*<<< orphan*/  send_space (unsigned int) ; 

__attribute__((used)) static int sir_tx_ir(struct rc_dev *dev, unsigned int *tx_buf,
		     unsigned int count)
{
	unsigned long flags;
	int i;

	local_irq_save(flags);
	for (i = 0; i < count;) {
		if (tx_buf[i])
			send_pulse(tx_buf[i]);
		i++;
		if (i >= count)
			break;
		if (tx_buf[i])
			send_space(tx_buf[i]);
		i++;
	}
	local_irq_restore(flags);

	return count;
}