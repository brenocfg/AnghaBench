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
 int /*<<< orphan*/  GPE0A_PME_B0_STS_BIT ; 
 int /*<<< orphan*/  GPE0A_STS_PORT ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void int0002_irq_ack(struct irq_data *data)
{
	outl(GPE0A_PME_B0_STS_BIT, GPE0A_STS_PORT);
}