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
struct netup_ci_state {int status; } ;
struct dvb_ca_en50221 {struct netup_ci_state* data; } ;

/* Variables and functions */
 int EINVAL ; 
 int NETUP_IRQ_DETAM ; 
 int ci_irq_flags () ; 
 int /*<<< orphan*/  netup_ci_set_irq (struct dvb_ca_en50221*,int) ; 

int netup_poll_ci_slot_status(struct dvb_ca_en50221 *en50221,
				     int slot, int open)
{
	struct netup_ci_state *state = en50221->data;

	if (0 != slot)
		return -EINVAL;

	netup_ci_set_irq(en50221, open ? (NETUP_IRQ_DETAM | ci_irq_flags())
			: NETUP_IRQ_DETAM);

	return state->status;
}