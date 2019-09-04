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
struct irq_domain {int dummy; } ;
struct TYPE_2__ {struct irq_domain* irqdomain; } ;

/* Variables and functions */
 TYPE_1__* ioapics ; 

__attribute__((used)) static inline struct irq_domain *mp_ioapic_irqdomain(int ioapic)
{
	return ioapics[ioapic].irqdomain;
}