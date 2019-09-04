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
struct irq_domain {int dummy; } ;
struct irq_alloc_info {int uv_limit; int uv_blade; unsigned long uv_offset; char* uv_name; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  X86_IRQ_ALLOC_TYPE_UV ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int /*<<< orphan*/  init_irq_alloc_info (struct irq_alloc_info*,int /*<<< orphan*/ ) ; 
 int irq_domain_alloc_irqs (struct irq_domain*,int,int /*<<< orphan*/ ,struct irq_alloc_info*) ; 
 int /*<<< orphan*/  uv_blade_to_memory_nid (int) ; 
 struct irq_domain* uv_get_irq_domain () ; 

int uv_setup_irq(char *irq_name, int cpu, int mmr_blade,
		 unsigned long mmr_offset, int limit)
{
	struct irq_alloc_info info;
	struct irq_domain *domain = uv_get_irq_domain();

	if (!domain)
		return -ENOMEM;

	init_irq_alloc_info(&info, cpumask_of(cpu));
	info.type = X86_IRQ_ALLOC_TYPE_UV;
	info.uv_limit = limit;
	info.uv_blade = mmr_blade;
	info.uv_offset = mmr_offset;
	info.uv_name = irq_name;

	return irq_domain_alloc_irqs(domain, 1,
				     uv_blade_to_memory_nid(mmr_blade), &info);
}