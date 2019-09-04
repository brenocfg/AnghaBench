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
struct irq_data {unsigned int hwirq; } ;

/* Variables and functions */
 unsigned int HW_IRQ_MX_BASE ; 
 int /*<<< orphan*/  MIENGSET ; 
 unsigned int XCHAL_INTTYPE_MASK_EXTERN_EDGE ; 
 unsigned int XCHAL_INTTYPE_MASK_EXTERN_LEVEL ; 
 unsigned int __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cached_irq_mask ; 
 int /*<<< orphan*/  intenable ; 
 int /*<<< orphan*/  set_er (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sr (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int xtensa_get_ext_irq_no (unsigned int) ; 

__attribute__((used)) static void xtensa_mx_irq_unmask(struct irq_data *d)
{
	unsigned int mask = 1u << d->hwirq;

	if (mask & (XCHAL_INTTYPE_MASK_EXTERN_EDGE |
				XCHAL_INTTYPE_MASK_EXTERN_LEVEL)) {
		set_er(1u << (xtensa_get_ext_irq_no(d->hwirq) -
					HW_IRQ_MX_BASE), MIENGSET);
	} else {
		mask |= __this_cpu_read(cached_irq_mask);
		__this_cpu_write(cached_irq_mask, mask);
		set_sr(mask, intenable);
	}
}