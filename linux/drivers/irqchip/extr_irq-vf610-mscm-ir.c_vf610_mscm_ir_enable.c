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
typedef  int u16 ;
struct vf610_mscm_ir_chip_data {int cpu_mask; scalar_t__ mscm_ir_base; } ;
struct irq_data {struct vf610_mscm_ir_chip_data* chip_data; int /*<<< orphan*/  hwirq; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 scalar_t__ MSCM_IRSPRC (int /*<<< orphan*/ ) ; 
 int MSCM_IRSPRC_CPEN_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  irq_chip_enable_parent (struct irq_data*) ; 
 int readw_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writew_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void vf610_mscm_ir_enable(struct irq_data *data)
{
	irq_hw_number_t hwirq = data->hwirq;
	struct vf610_mscm_ir_chip_data *chip_data = data->chip_data;
	u16 irsprc;

	irsprc = readw_relaxed(chip_data->mscm_ir_base + MSCM_IRSPRC(hwirq));
	irsprc &= MSCM_IRSPRC_CPEN_MASK;

	WARN_ON(irsprc & ~chip_data->cpu_mask);

	writew_relaxed(chip_data->cpu_mask,
		       chip_data->mscm_ir_base + MSCM_IRSPRC(hwirq));

	irq_chip_enable_parent(data);
}