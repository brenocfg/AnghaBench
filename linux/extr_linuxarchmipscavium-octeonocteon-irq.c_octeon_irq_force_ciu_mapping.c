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

/* Variables and functions */
 int irq_domain_associate (struct irq_domain*,int,int) ; 

__attribute__((used)) static int octeon_irq_force_ciu_mapping(struct irq_domain *domain,
					int irq, int line, int bit)
{
	return irq_domain_associate(domain, irq, line << 6 | bit);
}