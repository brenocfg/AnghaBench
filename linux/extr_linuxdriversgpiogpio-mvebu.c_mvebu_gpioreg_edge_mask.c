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
struct regmap {int dummy; } ;
struct mvebu_gpio_chip {int soc_variant; unsigned int offset; struct regmap* percpu_regs; struct regmap* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned int GPIO_EDGE_MASK_ARMADAXP_OFF (int) ; 
 unsigned int GPIO_EDGE_MASK_MV78200_OFF (int) ; 
 unsigned int GPIO_EDGE_MASK_OFF ; 
#define  MVEBU_GPIO_SOC_VARIANT_A8K 131 
#define  MVEBU_GPIO_SOC_VARIANT_ARMADAXP 130 
#define  MVEBU_GPIO_SOC_VARIANT_MV78200 129 
#define  MVEBU_GPIO_SOC_VARIANT_ORION 128 
 int smp_processor_id () ; 

__attribute__((used)) static inline void
mvebu_gpioreg_edge_mask(struct mvebu_gpio_chip *mvchip,
			struct regmap **map, unsigned int *offset)
{
	int cpu;

	switch (mvchip->soc_variant) {
	case MVEBU_GPIO_SOC_VARIANT_ORION:
	case MVEBU_GPIO_SOC_VARIANT_A8K:
		*map = mvchip->regs;
		*offset = GPIO_EDGE_MASK_OFF + mvchip->offset;
		break;
	case MVEBU_GPIO_SOC_VARIANT_MV78200:
		cpu = smp_processor_id();
		*map = mvchip->regs;
		*offset = GPIO_EDGE_MASK_MV78200_OFF(cpu);
		break;
	case MVEBU_GPIO_SOC_VARIANT_ARMADAXP:
		cpu = smp_processor_id();
		*map = mvchip->percpu_regs;
		*offset = GPIO_EDGE_MASK_ARMADAXP_OFF(cpu);
		break;
	default:
		BUG();
	}
}