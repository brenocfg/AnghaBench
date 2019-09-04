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
struct irq_data {unsigned int irq; } ;
typedef  int __u32 ;

/* Variables and functions */
 int EMR_BASE ; 
 int EVENT_BIT (unsigned int) ; 
 int LEVEL (unsigned int) ; 
 int inl (int) ; 
 int /*<<< orphan*/  outl (int,int) ; 

__attribute__((used)) static inline void enable_systemasic_irq(struct irq_data *data)
{
	unsigned int irq = data->irq;
	__u32 emr = EMR_BASE + (LEVEL(irq) << 4) + (LEVEL(irq) << 2);
	__u32 mask;

	mask = inl(emr);
	mask |= (1 << EVENT_BIT(irq));
	outl(mask, emr);
}