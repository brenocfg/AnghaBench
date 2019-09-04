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
struct cs5535_gpio_chip {int base; } ;

/* Variables and functions */
 unsigned int GPIO_NEGATIVE_EDGE_STS ; 
 unsigned int GPIO_POSITIVE_EDGE_STS ; 
 int inl (unsigned long) ; 
 int /*<<< orphan*/  outl (int,unsigned long) ; 

__attribute__((used)) static void errata_outl(struct cs5535_gpio_chip *chip, u32 val,
		unsigned int reg)
{
	unsigned long addr = chip->base + 0x80 + reg;

	/*
	 * According to the CS5536 errata (#36), after suspend
	 * a write to the high bank GPIO register will clear all
	 * non-selected bits; the recommended workaround is a
	 * read-modify-write operation.
	 *
	 * Don't apply this errata to the edge status GPIOs, as writing
	 * to their lower bits will clear them.
	 */
	if (reg != GPIO_POSITIVE_EDGE_STS && reg != GPIO_NEGATIVE_EDGE_STS) {
		if (val & 0xffff)
			val |= (inl(addr) & 0xffff); /* ignore the high bits */
		else
			val |= (inl(addr) ^ (val >> 16));
	}
	outl(val, addr);
}