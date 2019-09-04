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
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTC_CONTROL ; 
 int /*<<< orphan*/  intc_writel (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void omap_ack_irq(struct irq_data *d)
{
	intc_writel(INTC_CONTROL, 0x1);
}