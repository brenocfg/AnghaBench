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
struct TYPE_2__ {int irq_count; int* irq_map; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__ ppc4xx_hsta_msi ; 

__attribute__((used)) static int hsta_find_hwirq_offset(int hwirq)
{
	int irq;

	/* Find the offset given the hwirq */
	for (irq = 0; irq < ppc4xx_hsta_msi.irq_count; irq++)
		if (ppc4xx_hsta_msi.irq_map[irq] == hwirq)
			return irq;

	return -EINVAL;
}