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
struct mlxbf_tmfifo {TYPE_1__* irq_info; } ;
struct TYPE_2__ {int irq; } ;

/* Variables and functions */
 int MLXBF_TM_MAX_IRQ ; 
 int /*<<< orphan*/  disable_irq (int) ; 

__attribute__((used)) static void mlxbf_tmfifo_disable_irqs(struct mlxbf_tmfifo *fifo)
{
	int i, irq;

	for (i = 0; i < MLXBF_TM_MAX_IRQ; i++) {
		irq = fifo->irq_info[i].irq;
		fifo->irq_info[i].irq = 0;
		disable_irq(irq);
	}
}