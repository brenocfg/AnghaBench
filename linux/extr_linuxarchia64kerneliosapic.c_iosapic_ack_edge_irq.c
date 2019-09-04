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
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_complete_move (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_move_irq (struct irq_data*) ; 

__attribute__((used)) static void
iosapic_ack_edge_irq (struct irq_data *data)
{
	irq_complete_move(data->irq);
	irq_move_irq(data);
}