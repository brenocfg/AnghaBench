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
struct ixp4xx_irq {struct irq_domain* domain; } ;
struct irq_domain {int dummy; } ;

/* Variables and functions */
 struct ixp4xx_irq ixirq ; 

struct irq_domain *ixp4xx_get_irq_domain(void)
{
	struct ixp4xx_irq *ixi = &ixirq;

	return ixi->domain;
}