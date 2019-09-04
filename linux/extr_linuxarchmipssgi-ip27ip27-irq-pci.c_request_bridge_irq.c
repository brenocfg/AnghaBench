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
struct bridge_controller {int irq_cpu; } ;
typedef  int /*<<< orphan*/  nasid_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMPACT_TO_NASID_NODEID (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  REMOTE_HUB_CLR_INTR (int /*<<< orphan*/ ,int) ; 
 int alloc_level (int,int) ; 
 int allocate_irqno () ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 int /*<<< orphan*/  free_irqno (int) ; 
 int /*<<< orphan*/  intr_connect_level (int,int) ; 
 int /*<<< orphan*/  register_bridge_irq (int) ; 
 scalar_t__ unlikely (int) ; 

int request_bridge_irq(struct bridge_controller *bc)
{
	int irq = allocate_irqno();
	int swlevel, cpu;
	nasid_t nasid;

	if (irq < 0)
		return irq;

	/*
	 * "map" irq to a swlevel greater than 6 since the first 6 bits
	 * of INT_PEND0 are taken
	 */
	cpu = bc->irq_cpu;
	swlevel = alloc_level(cpu, irq);
	if (unlikely(swlevel < 0)) {
		free_irqno(irq);

		return -EAGAIN;
	}

	/* Make sure it's not already pending when we connect it. */
	nasid = COMPACT_TO_NASID_NODEID(cpu_to_node(cpu));
	REMOTE_HUB_CLR_INTR(nasid, swlevel);

	intr_connect_level(cpu, swlevel);

	register_bridge_irq(irq);

	return irq;
}