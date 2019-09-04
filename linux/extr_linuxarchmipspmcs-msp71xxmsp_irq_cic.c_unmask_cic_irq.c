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
struct irq_data {int irq; } ;

/* Variables and functions */
 int* CIC_VPE0_MSK_REG ; 
 int /*<<< orphan*/  LOCK_VPE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MSP_CIC_INTBASE ; 
 int /*<<< orphan*/  UNLOCK_VPE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cic_wmb () ; 
 int /*<<< orphan*/  flags ; 
 int get_current_vpe () ; 
 int /*<<< orphan*/  mtflags ; 

__attribute__((used)) static void unmask_cic_irq(struct irq_data *d)
{
	volatile u32   *cic_msk_reg = CIC_VPE0_MSK_REG;
	int vpe;
#ifdef CONFIG_SMP
	unsigned int mtflags;
	unsigned long  flags;

	/*
	* Make sure we have IRQ affinity.  It may have changed while
	* we were processing the IRQ.
	*/
	if (!cpumask_test_cpu(smp_processor_id(),
			      irq_data_get_affinity_mask(d)))
		return;
#endif

	vpe = get_current_vpe();
	LOCK_VPE(flags, mtflags);
	cic_msk_reg[vpe] |= (1 << (d->irq - MSP_CIC_INTBASE));
	UNLOCK_VPE(flags, mtflags);
	cic_wmb();
}