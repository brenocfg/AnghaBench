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
struct partition_desc {struct irq_domain* domain; } ;
struct irq_domain {int dummy; } ;

/* Variables and functions */

struct irq_domain *partition_get_domain(struct partition_desc *dsc)
{
	if (dsc)
		return dsc->domain;

	return NULL;
}