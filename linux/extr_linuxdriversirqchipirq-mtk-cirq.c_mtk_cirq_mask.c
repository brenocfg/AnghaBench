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
 int /*<<< orphan*/  CIRQ_MASK_SET ; 
 int /*<<< orphan*/  irq_chip_mask_parent (struct irq_data*) ; 
 int /*<<< orphan*/  mtk_cirq_write_mask (struct irq_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_cirq_mask(struct irq_data *data)
{
	mtk_cirq_write_mask(data, CIRQ_MASK_SET);
	irq_chip_mask_parent(data);
}