#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  picbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_IPI_SMP_FUNCTION ; 
 int /*<<< orphan*/  IRQ_IPI_SMP_RESCHEDULE ; 
 unsigned int SMP_CALL_FUNCTION ; 
 unsigned int SMP_RESCHEDULE_YOURSELF ; 
 unsigned int cpu_logical_map (int) ; 
 TYPE_1__* nlm_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_hwtid_to_node (unsigned int) ; 
 int /*<<< orphan*/  nlm_pic_send_ipi (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void nlm_send_ipi_single(int logical_cpu, unsigned int action)
{
	unsigned int hwtid;
	uint64_t picbase;

	/* node id is part of hwtid, and needed for send_ipi */
	hwtid = cpu_logical_map(logical_cpu);
	picbase = nlm_get_node(nlm_hwtid_to_node(hwtid))->picbase;

	if (action & SMP_CALL_FUNCTION)
		nlm_pic_send_ipi(picbase, hwtid, IRQ_IPI_SMP_FUNCTION, 0);
	if (action & SMP_RESCHEDULE_YOURSELF)
		nlm_pic_send_ipi(picbase, hwtid, IRQ_IPI_SMP_RESCHEDULE, 0);
}