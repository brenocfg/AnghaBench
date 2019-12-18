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
struct irq_source_info {int dummy; } ;
struct irq_service {struct irq_source_info const* info; } ;
typedef  enum dc_irq_source { ____Placeholder_dc_irq_source } dc_irq_source ;

/* Variables and functions */
 int DAL_IRQ_SOURCES_NUMBER ; 
 int DC_IRQ_SOURCE_INVALID ; 

const struct irq_source_info *find_irq_source_info(
	struct irq_service *irq_service,
	enum dc_irq_source source)
{
	if (source >= DAL_IRQ_SOURCES_NUMBER || source < DC_IRQ_SOURCE_INVALID)
		return NULL;

	return &irq_service->info[source];
}