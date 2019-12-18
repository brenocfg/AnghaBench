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
struct irq_info {int dummy; } ;

/* Variables and functions */
 struct irq_info* irq_get_handler_data (unsigned int) ; 

struct irq_info *info_for_irq(unsigned irq)
{
	return irq_get_handler_data(irq);
}