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
struct irq_alloc_info {struct cpumask const* mask; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct irq_alloc_info*,int /*<<< orphan*/ ,int) ; 

void init_irq_alloc_info(struct irq_alloc_info *info,
			 const struct cpumask *mask)
{
	memset(info, 0, sizeof(*info));
	info->mask = mask;
}