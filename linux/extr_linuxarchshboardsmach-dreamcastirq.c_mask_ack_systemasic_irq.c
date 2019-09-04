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
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ ESR_BASE ; 
 int EVENT_BIT (unsigned int) ; 
 int LEVEL (unsigned int) ; 
 int /*<<< orphan*/  disable_systemasic_irq (struct irq_data*) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static void mask_ack_systemasic_irq(struct irq_data *data)
{
	unsigned int irq = data->irq;
	__u32 esr = ESR_BASE + (LEVEL(irq) << 2);
	disable_systemasic_irq(data);
	outl((1 << EVENT_BIT(irq)), esr);
}