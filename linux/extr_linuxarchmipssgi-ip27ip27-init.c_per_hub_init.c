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
struct hub_data {int /*<<< orphan*/  irq_alloc_mask; int /*<<< orphan*/  h_cpus; } ;
typedef  int /*<<< orphan*/  nasid_t ;
typedef  int /*<<< orphan*/  cnodeid_t ;

/* Variables and functions */
 int BASE_PCI_IRQ ; 
 int /*<<< orphan*/  COMPACT_TO_NASID_NODEID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IIO_ICTO ; 
 int /*<<< orphan*/  IIO_ICTP ; 
 scalar_t__ INT_PEND0_BASELVL ; 
 scalar_t__ INT_PEND1_BASELVL ; 
 int IP_PEND0_6_63 ; 
 int /*<<< orphan*/  LOCAL_HUB_CLR_INTR (scalar_t__) ; 
 int /*<<< orphan*/  LOCAL_HUB_S (int /*<<< orphan*/ ,int) ; 
 int MSC_PANIC_INTR ; 
 int NI_BRDCAST_ERR_A ; 
 int /*<<< orphan*/  PI_INT_PEND_MOD ; 
 int /*<<< orphan*/  REMOTE_HUB_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hub_data* hub_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hub_init_mask ; 
 int /*<<< orphan*/  hub_rtc_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtalk_probe_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void per_hub_init(cnodeid_t cnode)
{
	struct hub_data *hub = hub_data(cnode);
	nasid_t nasid = COMPACT_TO_NASID_NODEID(cnode);
	int i;

	cpumask_set_cpu(smp_processor_id(), &hub->h_cpus);

	if (test_and_set_bit(cnode, hub_init_mask))
		return;
	/*
	 * Set CRB timeout at 5ms, (< PI timeout of 10ms)
	 */
	REMOTE_HUB_S(nasid, IIO_ICTP, 0x800);
	REMOTE_HUB_S(nasid, IIO_ICTO, 0xff);

	hub_rtc_init(cnode);
	xtalk_probe_node(cnode);

#ifdef CONFIG_REPLICATE_EXHANDLERS
	/*
	 * If this is not a headless node initialization,
	 * copy over the caliased exception handlers.
	 */
	if (get_compact_nodeid() == cnode) {
		extern char except_vec2_generic, except_vec3_generic;
		extern void build_tlb_refill_handler(void);

		memcpy((void *)(CKSEG0 + 0x100), &except_vec2_generic, 0x80);
		memcpy((void *)(CKSEG0 + 0x180), &except_vec3_generic, 0x80);
		build_tlb_refill_handler();
		memcpy((void *)(CKSEG0 + 0x100), (void *) CKSEG0, 0x80);
		memcpy((void *)(CKSEG0 + 0x180), &except_vec3_generic, 0x100);
		__flush_cache_all();
	}
#endif

	/*
	 * Some interrupts are reserved by hardware or by software convention.
	 * Mark these as reserved right away so they won't be used accidentally
	 * later.
	 */
	for (i = 0; i <= BASE_PCI_IRQ; i++) {
		__set_bit(i, hub->irq_alloc_mask);
		LOCAL_HUB_CLR_INTR(INT_PEND0_BASELVL + i);
	}

	__set_bit(IP_PEND0_6_63, hub->irq_alloc_mask);
	LOCAL_HUB_S(PI_INT_PEND_MOD, IP_PEND0_6_63);

	for (i = NI_BRDCAST_ERR_A; i <= MSC_PANIC_INTR; i++) {
		__set_bit(i, hub->irq_alloc_mask);
		LOCAL_HUB_CLR_INTR(INT_PEND1_BASELVL + i);
	}
}