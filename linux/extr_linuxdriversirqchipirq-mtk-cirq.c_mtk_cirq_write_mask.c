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
typedef  int u32 ;
struct mtk_cirq_chip_data {scalar_t__ base; } ;
struct irq_data {unsigned int hwirq; struct mtk_cirq_chip_data* chip_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void mtk_cirq_write_mask(struct irq_data *data, unsigned int offset)
{
	struct mtk_cirq_chip_data *chip_data = data->chip_data;
	unsigned int cirq_num = data->hwirq;
	u32 mask = 1 << (cirq_num % 32);

	writel_relaxed(mask, chip_data->base + offset + (cirq_num / 32) * 4);
}